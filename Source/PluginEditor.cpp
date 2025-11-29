#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (DelayPluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), attOutGain(p.getProcessorValueTreeState(), PluginConfig::paramIDOutGain.getParamID(), sldrOutGain),
        attDelayTime(p.getProcessorValueTreeState(), PluginConfig::paramIDDelayTime.getParamID(), sldrDelayTime)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (EditorDefaults::defaultWindowWidth, EditorDefaults::defaultWindowHeight);

    // Add + configure child components
    addAndMakeVisible(sldrOutGain);
    addAndMakeVisible(lblOutGain);
    addAndMakeVisible(sldrDelayTime);
    addAndMakeVisible(lblDelayTime);
    addAndMakeVisible(sldrDryWet);
    addAndMakeVisible(lblDryWet);

    sldrOutGain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sldrOutGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, EditorDefaults::defaultSliderTextBoxReadOnly, EditorDefaults::defaultSliderTextBoxWidth, EditorDefaults::defaultSliderTextBoxHeight);
    sldrOutGain.setRange(PluginConfig::minOutGain, PluginConfig::maxOutGain, PluginConfig::sliderStepDefault);
    sldrOutGain.setTextValueSuffix("dB");
    lblOutGain.setText(PluginConfig::paramNameOutGain, juce::NotificationType::dontSendNotification);
    lblOutGain.attachToComponent(&sldrOutGain, true);

    sldrDelayTime.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sldrDelayTime.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, EditorDefaults::defaultSliderTextBoxReadOnly, EditorDefaults::defaultSliderTextBoxWidth, EditorDefaults::defaultSliderTextBoxHeight);
    sldrDelayTime.setRange(PluginConfig::minDelayTime, PluginConfig::maxDelayTime, PluginConfig::sliderStepDefault);
    lblDelayTime.setText(PluginConfig::paramNameDelayTime, juce::NotificationType::dontSendNotification);
    lblDelayTime.attachToComponent(&sldrDelayTime, true);

    sldrDryWet.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sldrDryWet.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, EditorDefaults::defaultSliderTextBoxReadOnly, EditorDefaults::defaultSliderTextBoxWidth, EditorDefaults::defaultSliderTextBoxHeight);
    sldrDryWet.setRange(PluginConfig::minDryWet, PluginConfig::maxDryWet, PluginConfig::sliderStepDryWet);
    lblDryWet.setText(PluginConfig::paramNameDryWet, juce::NotificationType::dontSendNotification);
    lblDryWet.attachToComponent(&sldrDryWet, true);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

// Lay out child components
void AudioPluginAudioProcessorEditor::resized()
{
    const juce::Rectangle<int> bounds = getLocalBounds();
    sldrDelayTime.setBounds(bounds.getCentreX() - EditorDefaults::defaultSliderWidth / 2, bounds.getCentreY() - EditorDefaults::defaultSliderHeight / 2,
                             EditorDefaults::defaultSliderWidth, EditorDefaults::defaultSliderHeight);

    // Position elements relative to delay time, which is the main parameter.
    const juce::Rectangle<int> delayTimeBounds = sldrDelayTime.getBounds();
    sldrOutGain.setBounds(delayTimeBounds.getX(), delayTimeBounds.getY() - EditorDefaults::defaultSliderHeight - EditorDefaults::sliderMarginY, EditorDefaults::defaultSliderWidth, EditorDefaults::defaultSliderHeight);
    sldrDryWet.setBounds(delayTimeBounds.getX(), delayTimeBounds.getBottom() + EditorDefaults::sliderMarginY, EditorDefaults::defaultSliderWidth, EditorDefaults::defaultSliderHeight);
}
