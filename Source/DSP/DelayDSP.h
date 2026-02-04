//
// Created by Joe on 25/11/2025.
//

#ifndef BSGDELAY_DELAYDSP_H
#define BSGDELAY_DELAYDSP_H

#include <juce_dsp/juce_dsp.h>

class DelayDSP
{
public:
    void prepareToPlay(int numChannels, float sampleRate, int blockSize) noexcept;
    void processBlock(juce::AudioBuffer<float>& buffer, int blockSize, bool isPingPong) noexcept;

    // Delay time is in seconds. No need to convert units in this class
    void setTargetDelayTime(const float targetDelayTime) { m_targetDelayTime = targetDelayTime; }
    void smoothenDelayTime() { m_currentDelayTime += (m_targetDelayTime - m_currentDelayTime) * m_smootherCoefficient; }

    void setDelayTime(const float seconds) { delayLine.setDelay(convertSecondsToSamples(seconds)); }
    void setFeedback(const float feedback) { m_feedback = feedback; }
    void setDryWet(const float dryWet) { m_dryWet = dryWet; }
    void setStereoWidth(const float stereoWidth) { m_stereoWidth = stereoWidth; }

private:
    juce::dsp::DelayLine<float> delayLine {};

    float m_sampleRate { };
    float m_feedback { };
    float m_dryWet { };
    float m_stereoWidth { };

    float m_currentDelayTime { 0.0f };
    float m_targetDelayTime { 0.0f };
    float m_smootherCoefficient { 0.0f };

    [[nodiscard]] int convertSecondsToSamples(float seconds) const;
};


#endif //BSGDELAY_DELAYDSP_H