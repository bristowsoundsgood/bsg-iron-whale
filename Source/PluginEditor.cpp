#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (DelayPluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), stateRef(p.getProcessorValueTreeState())
{
    juce::ignoreUnused (processorRef);

    // Aggregate dials into respective groups
    delayGroup.setText("Delay");
    delayGroup.setTextLabelPosition(juce::Justification::centred);
    delayGroup.addAndMakeVisible(dialDelayTime);
    addAndMakeVisible(delayGroup);

    feedbackGroup.setText("Feedback");
    feedbackGroup.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(feedbackGroup);

    mixGroup.setText("Mix");
    mixGroup.setTextLabelPosition(juce::Justification::centred);
    mixGroup.addAndMakeVisible(dialDryWet);
    mixGroup.addAndMakeVisible(dialOutGain);
    addAndMakeVisible(mixGroup);

    setSize(GUIDefaults::windowWidth, GUIDefaults::windowHeight);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
}

// Lay out child components
void AudioPluginAudioProcessorEditor::resized()
{
    const juce::Rectangle<int> bounds = getLocalBounds();

    constexpr int dialWidth = GUIDefaults::groupWidth - 10;
    constexpr int dialHeight = dialWidth + 30;

    delayGroup.setBounds(GUIDefaults::marginSide, GUIDefaults::marginTop,
        GUIDefaults::groupWidth, GUIDefaults::groupHeight);

    dialDelayTime.setBounds(delayGroup.getLocalBounds().getCentreX() - dialWidth / 2, delayGroup.getLocalBounds().getTopLeft().getY() + GUIDefaults::marginTop,
        dialWidth, dialHeight);

    feedbackGroup.setBounds(delayGroup.getBounds().getRight() + GUIDefaults::marginSide, GUIDefaults::marginTop,
        bounds.getWidth() - 2 * ((2 * GUIDefaults::marginSide) + GUIDefaults::groupWidth), GUIDefaults::groupHeight);

    mixGroup.setBounds(bounds.getRight() - GUIDefaults::groupWidth - GUIDefaults::marginSide, GUIDefaults::marginTop,
        GUIDefaults::groupWidth, GUIDefaults::groupHeight);

    dialOutGain.setBounds(mixGroup.getLocalBounds().getCentreX() - dialWidth / 2, mixGroup.getLocalBounds().getTopLeft().getY() + GUIDefaults::marginTop,
        dialWidth, dialHeight);

    dialDryWet.setBounds(mixGroup.getLocalBounds().getCentreX() - dialWidth / 2, dialOutGain.getBottom() + GUIDefaults::marginTop,
        dialWidth, dialHeight);
}
