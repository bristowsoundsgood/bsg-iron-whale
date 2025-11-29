//
// Created by Joe Bristow on 14/11/2025.
//
#pragma once
#ifndef PLUGINPARAMETERS_H
#define PLUGINPARAMETERS_H
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace PluginConfig
{
    // General
    static constexpr float sliderStepDefault {0.01f};
    static constexpr float sliderStepDelayTime {0.1f};
    static constexpr float sliderStepDryWet {1.0f};

    // Gain
    static constexpr float minOutGain {-64.0f};
    static constexpr float maxOutGain {24.0f};
    static constexpr float defaultOutGain {0.0f};
    static const juce::ParameterID paramIDOutGain {"outputGain", 1};
    static const juce::String paramNameOutGain {"Output Gain"};

    // Delay
    static constexpr float minDelayTime {5.0f};
    static constexpr float maxDelayTime {5000.0f};
    static constexpr float defaultDelayTime {50.0f};
    static constexpr float skewFactorDelay {0.25f};
    static const juce::ParameterID paramIDDelayTime {"delayTime", 1};
    static const juce::String paramNameDelayTime {"Delay Time"};
    static const juce::NormalisableRange<float> delayTimeRange {minDelayTime, maxDelayTime, sliderStepDelayTime, skewFactorDelay};

    // Dry/wet
    static constexpr float minDryWet {0.0f};
    static constexpr float maxDryWet {100.0f};
    static const juce::ParameterID paramIDDryWet {"dryWet", 1};
    static const juce::String paramNameDryWet {"Dry/Wet"};

    // SmoothedValue settings
    static constexpr float rampSmoothTime {0.0005f};
}

class PluginParameters
{
public:
    // Accepts APVTS as dependency to store the addresses of the parameters found in state manager
    PluginParameters(const juce::AudioProcessorValueTreeState& stateManager);

    // Called upon PluginProcessor initialisation
    [[nodiscard]] static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() noexcept;

    // Accessor methods
    [[nodiscard]] float getOutputGainDB() { return m_smootherGain.getNextValue(); }
    [[nodiscard]] float getDelayTimeSeconds() const { return m_paramDelayTime->get() / 1000.0f; }

    // Parameter smoothing methods
    void prepare(double sampleRate) noexcept;
    void reset() noexcept;
    void update() noexcept;

private:
    // Parameter objects
    juce::AudioParameterFloat* m_paramOutGain {};
    juce::AudioParameterFloat* m_paramDelayTime {};

    // Parameter smoothing
    juce::SmoothedValue<float> m_smootherGain {};
};

#endif //PLUGINPARAMETERS_H
