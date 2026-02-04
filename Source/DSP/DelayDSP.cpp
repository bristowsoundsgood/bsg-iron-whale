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
    spec.sampleRate = static_cast<double>(sampleRate);
    spec.maximumBlockSize = static_cast<juce::uint32>(blockSize);
    spec.numChannels = static_cast<juce::uint32>(numChannels);
    delayLine.prepare(spec);

    // Use max delay time to set delay line size.
    const int maxDelayInSamples(convertSecondsToSamples(PluginConfig::maxDelayTime / 1000.0f));
    delayLine.setMaximumDelayInSamples(maxDelayInSamples);

    // Clear internal state to avoid undefined behaviour
    delayLine.reset();
}

void DelayDSP::processBlock(juce::AudioBuffer<float>& buffer, const int blockSize, const bool isPingPong) noexcept
{
    for (int sample = 0; sample < blockSize; ++sample)
    {
        // Step delay time toward target value
        smoothenDelayTime();
        const float smoothedDelayTime { m_currentDelayTime };
        setDelayTime(smoothedDelayTime);

        const float dryL { buffer.getSample(0, sample) };
        const float dryR { buffer.getSample(1, sample) };

        const float wetL { delayLine.popSample(0, delayLine.getDelay()) };
        const float wetR { delayLine.popSample(1, delayLine.getDelay()) };

        const float feedbackL { wetL * m_feedback };
        const float feedbackR { wetR * m_feedback };

        // Cross feedback lines. If feedback is 0, then only the dry will be pushed.
        if (isPingPong)
        {
            constexpr float panL { 0.0f };
            constexpr float panR { 1.0f };
            const float mono { (dryL + dryR) * 0.5f };
            delayLine.pushSample(0, panL * mono + feedbackR);
            delayLine.pushSample(1, panR * mono + feedbackL);
        }

        else
        {
            delayLine.pushSample(0, dryL + feedbackL);
            delayLine.pushSample(1, dryR + feedbackR);
        }

        // Mix dry and wet signal. 100% wet = only wet. 100% dry = only dry. 50% wet = dry/wet in equal amounts.
        const float outL { dryL * (1.0f - m_dryWet)  + wetL * m_dryWet };
        const float outR { dryR * (1.0f - m_dryWet)  + wetR * m_dryWet };

        buffer.setSample(0, sample, outL);
        buffer.setSample(1, sample, outR);
    }
}


