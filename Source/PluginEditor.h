#pragma once

#include "PluginProcessor.h"
#include "PluginParameters.h"
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
namespace EditorDefaults
{
    static constexpr int defaultWindowWidth {400};
    static constexpr int defaultWindowHeight {600};
    static constexpr int defaultSliderWidth {150};
    static constexpr int defaultSliderHeight {150};
    static constexpr int defaultSliderTextBoxWidth {70};
    static constexpr int defaultSliderTextBoxHeight {30};
    static constexpr bool defaultSliderTextBoxReadOnly {false};

    static constexpr int sliderMarginY {20};
}

class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (DelayPluginProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DelayPluginProcessor& processorRef;

    // Declare child components
    juce::Slider sldrOutGain;
    juce::Label lblOutGain;
    juce::Slider sldrDelayTime;
    juce::Label lblDelayTime;
    juce::Slider sldrDryWet;
    juce::Label lblDryWet;

    // Parameter attachments
    juce::AudioProcessorValueTreeState::SliderAttachment attOutGain;
    juce::AudioProcessorValueTreeState::SliderAttachment attDelayTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
