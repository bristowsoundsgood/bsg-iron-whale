#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "GainDSP.h"

namespace DelayParameters
{
    static constexpr float defaultSliderStep {0.01f};

    static constexpr float minOutputGain {-64.0f};
    static constexpr float maxOutputGain {24.0f};
    static constexpr float defaultOutputGain {0.0f};
    static const juce::ParameterID paramIDOutputGain {"outputGain", 1};
    static const juce::String paramNameOutputGain {"Output Gain"};

}

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    [[nodiscard]] juce::AudioProcessorValueTreeState& getProcessorValueTreeState();
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    // DSP objects. One for each channel.
    std::vector<GainDSP> gainDsps {};

    // Parameter pointers
    juce::AudioParameterFloat* paramOutputGain {};

    // State Management
    juce::AudioProcessorValueTreeState state;
    [[nodiscard]] juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
