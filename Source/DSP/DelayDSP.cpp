//
// Created by Joe on 25/11/2025.
//

#include "DelayDSP.h"
#include "../PluginParameters.h"

// Assumes the passed value is in seconds, not milliseconds!
int DelayDSP::convertSecondsToSamples(const float seconds) const
{
    return static_cast<int>(std::ceil(seconds * m_sampleRate));
}

void DelayDSP::prepareToPlay(const int numChannels, const float sampleRate, const int blockSize) noexcept
{
    m_sampleRate = sampleRate;

    // This equation emulates the exponential decay of an analog filter. Used to modulate delay time.
    m_smootherCoefficient = 1.0f - std::exp(-1.0f / (0.2f * m_sampleRate));

    // Prepare delay line (ProcessSpec encapsulates contextual information)
    juce::dsp::ProcessSpec spec {};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(blockSize);
    spec.numChannels = numChannels;
    delayLine.prepare(spec);

    // Use max delay time to set delay line size.
    const int maxDelayInSamples(convertSecondsToSamples(PluginConfig::maxDelayTime / 1000.0f));
    delayLine.setMaximumDelayInSamples(maxDelayInSamples);

    // Clear internal state to avoid undefined behaviour
    delayLine.reset();
}

void DelayDSP::processBlock(const int channel, float* block, const int blockSize) noexcept
{
    for (int sample = 0; sample < blockSize; ++sample)
    {
        // Step delay time toward target value
        smoothenDelayTime();
        const float smoothedDelayTime = m_currentDelayTime;
        setDelayTime(smoothedDelayTime);

        const float drySample = block[sample];
        const float wetSample = delayLine.popSample(channel, delayLine.getDelay());
        const float feedbackSample = wetSample * m_feedback;

        // If feedbackSample is 0, then only the dry will be pushed.
        delayLine.pushSample(channel, drySample + feedbackSample);

        // Mix dry and wet signal. 100% wet = only wet. 100% dry = only dry. 50% wet = dry/wet in equal amounts.
        const float outputSample = (1.0f - m_dryWet) * drySample + m_dryWet * wetSample;
        block[sample] = outputSample;
    }
}


