//
// Created by Joe Bristow on 02/12/2025.
//

#include "RotaryDial.h"

RotaryDial::RotaryDial(juce::AudioProcessorValueTreeState& state, const juce::ParameterID& parameterID,
    const juce::String& labelText) : attachment(state, parameterID.getParamID(), slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                            GUIDefaults::sliderTextBoxReadOnly, GUIDefaults::sliderTextBoxWidth,
                            GUIDefaults::sliderTextBoxHeight);
    addAndMakeVisible(slider);

    label.setText(labelText, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setBorderSize(juce::BorderSize<int>(0));
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    setSize(GUIDefaults::sliderWidth, GUIDefaults::sliderHeight + GUIDefaults::labelHeight);
}

RotaryDial::~RotaryDial()
{
}

void RotaryDial::resized()
{
    juce::Rectangle<int> totalArea = getLocalBounds();

    // Slider area occupies top portion
    const juce::Rectangle<int> knobArea = totalArea.removeFromTop(totalArea.getHeight() * 0.8f);
    slider.setBounds(knobArea);

    // Label area occupies remaining bottom portion
    label.setBounds(totalArea);
}

