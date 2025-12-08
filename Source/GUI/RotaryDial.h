//
// Created by Joe Bristow on 02/12/2025.
//

#ifndef ROTARYKNOB_H
#define ROTARYKNOB_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "DefaultSkin.h"
#include "../PluginParameters.h"

class RotaryDial : public juce::Component {
public:
    RotaryDial(juce::AudioProcessorValueTreeState& state, const juce::ParameterID& parameterID,
        const juce::String& labelText);
    ~RotaryDial() override;

    juce::Slider slider;
    juce::Label label;
    juce::AudioProcessorValueTreeState::SliderAttachment attachment;

    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryDial)
};



#endif //ROTARYKNOB_H
