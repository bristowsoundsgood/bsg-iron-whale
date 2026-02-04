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
    static constexpr float intervalDefault {0.01f};
    static constexpr float intervalDelayTime {0.1f};

    // Gain
    static const juce::ParameterID paramIDOutGain {"outputGain", 1};
    static const juce::String paramNameOutGain {"Output Gain"};
    static const juce::String labelTextOutGain {"OUT GAIN"};
    static constexpr float minOutGain {-64.0f};
    static constexpr float maxOutGain {24.0f};
    static constexpr float defaultOutGain {0.0f};
    static const juce::NormalisableRange outputGainRange {minOutGain, maxOutGain, intervalDefault};

    // Delay
    static const juce::ParameterID paramIDDelayTime {"delayTime", 1};
    static const juce::String paramNameDelayTime {"Delay Time"};
    static const juce::String labelTextDelayTime {"TIME"};
    static constexpr float minDelayTime {5.0f};
    static constexpr float maxDelayTime {5000.0f};
    static constexpr float defaultDelayTime {50.0f};
    static constexpr float skewFactorDelay {0.25f};
    static const juce::NormalisableRange delayTimeRange {minDelayTime, maxDelayTime, intervalDelayTime, skewFactorDelay};

    // Feedback
    static const juce::ParameterID paramIDFeedback {"feedback", 1};
    static const juce::String paramNameFeedback {"Feedback"};
    static const juce::String labelTextFeedback {"FEEDBACK"};
    static constexpr float minFeedback {0.0f};
    static constexpr float maxFeedback {0.95f};
    static constexpr float defaultFeedback {0.5f};
    static const juce::NormalisableRange feedbackRange {minFeedback, maxFeedback, intervalDefault};

    // Dry/Wet
    static const juce::ParameterID paramIDDryWet {"dryWet", 1};
    static const juce::String paramNameDryWet {"Dry/Wet"};
    static const juce::String labelTextDryWet {"DRY / WET"};
    static constexpr float minDryWet {0.0f};
    static constexpr float maxDryWet {1.0f};
    static constexpr float defaultDryWet {0.5f};
    static const juce::NormalisableRange dryWetRange {minDryWet, maxDryWet, intervalDefault};

    // Stereo Width
    static const juce::ParameterID paramIDStereoWidth { "stereoWidth", 1 };
    static const juce::String paramNameStereoWidth { "Stereo Width" };
    static const juce::String labelTextStereoWidth { "WIDTH" };
    static constexpr float minStereoWidth { 0.0f };
    static constexpr float maxStereoWidth { 1.0f };
    static constexpr float defaultStereoWidth { 0.5f };
    static const juce::NormalisableRange stereoWidthRange { minStereoWidth, maxStereoWidth, intervalDefault };

    // Ping-pong Toggle
    static const juce::ParameterID paramIDPingPongToggle {"pingPong", 1};
    static const juce::String paramNamePingPongToggle {"Ping Pong"};
    static constexpr bool defaultPingPongToggle {false};

    // SmoothedValue settings
    static constexpr float rampSmoothTime {0.0005f};
}

class PluginParameters
{
public:
    // Accepts APVTS as dependency to store the addresses of the parameters found in state manager
    explicit PluginParameters(const juce::AudioProcessorValueTreeState& stateManager);

    // Called upon PluginProcessor initialisation
    [[nodiscard]] static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() noexcept;

    // Accessor methods
    [[nodiscard]] float getOutputGainDB() { return m_smootherGain.getNextValue(); }
    [[nodiscard]] float getDelayTimeSeconds() const { return m_paramDelayTime->get() / 1000.0f; } // Convert seconds to ms
    [[nodiscard]] float getDryWet() { return m_smootherDryWet.getNextValue(); }  // Returns float between 0.0 and 1.0 to simplify DSP
    [[nodiscard]] float getFeedback() { return m_smootherFeedback.getNextValue(); }
    [[nodiscard]] float getStereoWidth() const { return m_paramStereoWidth->get(); }
    [[nodiscard]] bool getPingPongToggle() const { return m_paramPingPong->get(); }

    void setPingPongToggle(const bool isToggled) const { *m_paramPingPong = isToggled; }

    // Parameter smoothing methods
    void prepare(double sampleRate) noexcept;
    void reset() noexcept;
    void update() noexcept;

private:
    // Parameter objects
    juce::AudioParameterFloat* m_paramOutGain {};
    juce::AudioParameterFloat* m_paramDelayTime {};
    juce::AudioParameterFloat* m_paramDryWet {};
    juce::AudioParameterFloat* m_paramFeedback {};
    juce::AudioParameterFloat* m_paramStereoWidth {};
    juce::AudioParameterBool* m_paramPingPong {};

    // Parameter smoothing
    juce::SmoothedValue<float> m_smootherGain {};
    juce::SmoothedValue<float> m_smootherDryWet {};
    juce::SmoothedValue<float> m_smootherFeedback {};
};

#endif //PLUGINPARAMETERS_H
