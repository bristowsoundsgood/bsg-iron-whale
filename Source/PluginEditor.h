#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"
#include "GUI/DefaultSkin.h"
#include "GUI/RotaryDial.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (DelayPluginProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to access the processor object that created it.
    DelayPluginProcessor& processorRef;
    juce::AudioProcessorValueTreeState& stateRef;

    juce::GroupComponent delayGroup;
    juce::GroupComponent feedbackGroup;
    juce::GroupComponent mixGroup;

    // Declare child components
    RotaryDial dialDelayTime {stateRef, PluginConfig::paramIDDelayTime, PluginConfig::labelTextDelayTime};
    RotaryDial dialDryWet {stateRef, PluginConfig::paramIDDryWet, PluginConfig::labelTextDryWet};
    RotaryDial dialOutGain {stateRef, PluginConfig::paramIDOutGain, PluginConfig::labelTextOutGain};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
