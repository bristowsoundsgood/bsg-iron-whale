//
// Created by Joe Bristow on 04/12/2025.
//

#include "DefaultSkin.h"

RotaryDialLookAndFeel::RotaryDialLookAndFeel()
{
    setColour(juce::Slider::rotarySliderFillColourId, Colours::Dial::dialFill);

    // setColour(juce::Label::textColourId, Colours::Dial::label);
    // setColour(juce::Slider::textBoxTextColourId, Colours::Dial::label);
}

RotaryDialLookAndFeel& RotaryDialLookAndFeel::instance()
{
    static RotaryDialLookAndFeel INSTANCE;
    return INSTANCE;
}


