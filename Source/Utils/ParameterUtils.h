//
// Created by Joe on 26/11/2025.
//

#ifndef BSGDELAY_PARAMETERUTILS_H
#define BSGDELAY_PARAMETERUTILS_H

#include <juce_audio_basics/juce_audio_basics.h>

class ParameterUtils
{
public:
    static juce::String stringFromMilliseconds(float value, int);
    static juce::String stringFromPercent(float value, int);
    static juce::String stringFromDecibels(float value, int);

    static float millisecondsFromString(const juce::String& text);
};


#endif //BSGDELAY_PARAMETERUTILS_H