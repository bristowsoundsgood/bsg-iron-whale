#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // Add + configure child components
    addAndMakeVisible(sldrOutputGain);
    addAndMakeVisible(lblOutputGain);

    sldrOutputGain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sldrOutputGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, EditorDefaults::DEFAULT_SLIDER_TBOX_READONLY, EditorDefaults::DEFAULT_SLIDER_TBOX_WIDTH, EditorDefaults::DEFAULT_SLIDER_TBOX_HEIGHT);
    sldrOutputGain.setRange(EditorDefaults::DEFAULT_SLIDER_MIN, EditorDefaults::DEFAULT_SLIDER_MAX, EditorDefaults::DEFAULT_SLIDER_STEP);
    sldrOutputGain.setTextValueSuffix("dB");
    lblOutputGain.setText("Output Gain", juce::NotificationType::dontSendNotification);
    lblOutputGain.attachToComponent(&sldrOutputGain, true);
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

void AudioPluginAudioProcessorEditor::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();

    // Lay out child components
    sldrOutputGain.setBounds(bounds.getCentreX() - EditorDefaults::DEFAULT_SLIDER_WIDTH / 2, bounds.getCentreY() - EditorDefaults::DEFAULT_SLIDER_HEIGHT / 2,
                             EditorDefaults::DEFAULT_SLIDER_WIDTH, EditorDefaults::DEFAULT_SLIDER_HEIGHT);
}
