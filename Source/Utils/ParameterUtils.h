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
    static juce::String stringFromPercentNormalised(float value, int);
    static juce::String stringFromDecibels(float value, int);
    static float millisecondsFromString(const juce::String& text);
    static float feedbackNormalisedFromString(const juce::String& text);
    static float dryWetNormalisedFromString(const juce::String& text);

    ParameterUtils() = delete;
};


#endif //BSGDELAY_PARAMETERUTILS_H