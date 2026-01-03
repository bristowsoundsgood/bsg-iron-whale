#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (DelayPluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), stateRef(p.getProcessorValueTreeState())
{
    juce::ignoreUnused (processorRef);

    // Aggregate dials into respective groups
    delayGroup.setText("DELAY");
    delayGroup.setTextLabelPosition(juce::Justification::centred);
    delayGroup.addAndMakeVisible(dialDelayTime);
    addAndMakeVisible(delayGroup);

    feedbackGroup.setText("FEEDBACK");
    feedbackGroup.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(feedbackGroup);

    mixGroup.setText("MIX");
    mixGroup.setTextLabelPosition(juce::Justification::centred);
    mixGroup.addAndMakeVisible(dialDryWet);
    mixGroup.addAndMakeVisible(dialOutGain);
    addAndMakeVisible(mixGroup);

    setLookAndFeel(&MainLookAndFeel::instance());
    setSize(Dimensions::windowWidth, Dimensions::windowHeight);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::background);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
}

// Lay out child components
void AudioPluginAudioProcessorEditor::resized()
{
    const juce::Rectangle<int> bounds = getLocalBounds();

    constexpr int dialWidth = Dimensions::groupWidth - 30;
    constexpr int dialHeight = dialWidth + 30;

    delayGroup.setBounds(Dimensions::marginSide, Dimensions::marginTop,
        Dimensions::groupWidth, Dimensions::groupHeight);

    dialDelayTime.setBounds(delayGroup.getLocalBounds().getCentreX() - dialWidth / 2, delayGroup.getLocalBounds().getTopLeft().getY() + Dimensions::marginTop,
        dialWidth, dialHeight);

    feedbackGroup.setBounds(delayGroup.getBounds().getRight() + Dimensions::marginSide, Dimensions::marginTop,
        bounds.getWidth() - 2 * ((2 * Dimensions::marginSide) + Dimensions::groupWidth), Dimensions::groupHeight);

    mixGroup.setBounds(bounds.getRight() - Dimensions::groupWidth - Dimensions::marginSide, Dimensions::marginTop,
        Dimensions::groupWidth, Dimensions::groupHeight);

    dialOutGain.setBounds(mixGroup.getLocalBounds().getCentreX() - dialWidth / 2, mixGroup.getLocalBounds().getTopLeft().getY() + Dimensions::marginTop,
        dialWidth, dialHeight);

    dialDryWet.setBounds(mixGroup.getLocalBounds().getCentreX() - dialWidth / 2, dialOutGain.getBottom() + Dimensions::marginTop,
        dialWidth, dialHeight);
}
