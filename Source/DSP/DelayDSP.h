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
    void processBlock(int channel, float* block, int blockSize) noexcept;

    // Delay time is in seconds. No need to convert units in this class
    void setTargetDelayTime(const float targetDelayTime) { m_targetDelayTime = targetDelayTime; }
    void smoothenDelayTime() { m_currentDelayTime += (m_targetDelayTime - m_currentDelayTime) * m_smootherCoefficient; }

    void setDelayTime(const float seconds) { delayLine.setDelay(convertSecondsToSamples(seconds)); }
    void setFeedback(const float feedback) { m_feedback = feedback; }
    void setDryWet(const float dryWet) { m_dryWet = dryWet;  }

private:
    float m_sampleRate {};
    float m_feedback {};
    float m_dryWet {};
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine {};

    float m_currentDelayTime {0.0f};
    float m_targetDelayTime {0.0f};
    float m_smootherCoefficient {0.0f};

    [[nodiscard]] int convertSecondsToSamples(float seconds) const;
};


#endif //BSGDELAY_DELAYDSP_H