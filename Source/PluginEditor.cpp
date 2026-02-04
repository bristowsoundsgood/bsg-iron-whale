#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (DelayPluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), stateRef(p.getProcessorValueTreeState()),
        attachBtnPingPong(stateRef, PluginConfig::paramIDPingPongToggle.getParamID(), btnPingPong)
{
    juce::ignoreUnused (processorRef);

    // Aggregate dials into respective groups
    delayGroup.setText("DELAY");
    delayGroup.setTextLabelPosition(juce::Justification::centred);
    delayGroup.addAndMakeVisible(dialDelayTime);
    addAndMakeVisible(delayGroup);

    feedbackGroup.setText("FEEDBACK");
    feedbackGroup.setTextLabelPosition(juce::Justification::centred);
    feedbackGroup.addAndMakeVisible(dialFeedback);
    feedbackGroup.addAndMakeVisible(dialStereoWidth);
    feedbackGroup.addAndMakeVisible(btnPingPong);
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

    dialFeedback.setBounds(feedbackGroup.getLocalBounds().getCentreX() - dialWidth / 2, feedbackGroup.getLocalBounds().getTopLeft().getY() + Dimensions::marginTop,
        dialWidth, dialHeight);

    // Using .getBounds() to get dial coords. .getLocalBounds() references the parent (feedbackGroup)
    dialStereoWidth.setBounds(dialFeedback.getBounds().getRight() + Dimensions::marginTop, dialFeedback.getBounds().getY(),
        dialWidth, dialHeight);

    btnPingPong.setBounds(dialFeedback.getLocalBounds().getX(), dialFeedback.getBounds().getY() + Dimensions::dialBufferY,
        Dimensions::btnWidth, Dimensions::btnHeight);

    dialDryWet.setBounds(mixGroup.getLocalBounds().getCentreX() - dialWidth / 2, dialOutGain.getBottom() + Dimensions::marginTop,
        dialWidth, dialHeight);
}
