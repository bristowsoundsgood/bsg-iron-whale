//
// Created by Joe on 26/11/2025.
//

#include "ParameterUtils.h"
#include "../PluginParameters.h"

// Precision depends on value magnitude
juce::String ParameterUtils::stringFromMilliseconds(const float value, int)
{
    if (value < 10.0f)
    {
        return juce::String(value, 2) + " ms";
    }

    else if (value < 100.0f)
    {
        return juce::String(value, 1) + " ms";
    }

    else if (value < 1000.0f)
    {
        return juce::String(static_cast<int>(value)) + " ms";
    }

    else
    {
        return juce::String(value * 0.001f, 2) + " s";
    }
}

juce::String ParameterUtils::stringFromDecibels(const float value, int)
{
    return juce::String(value, 2) + "dB";
}

juce::String ParameterUtils::stringFromPercentNormalised(const float value, int)
{
    return juce::String(value * 100.0f) + "%";
}


float ParameterUtils::millisecondsFromString(const juce::String& text)
{
    const float value = text.getFloatValue();

    if (text.endsWithIgnoreCase("ms"))
    {
        return value;
    }

    // 1.0s -> 1000.0ms (also converts to seconds if ms is not possible with constraints)
    else if (text.endsWithIgnoreCase("s") || value < PluginConfig::minDelayTime)
    {
        return value * 1000.0f;
    }

    else
    {
        return PluginConfig::defaultDelayTime;
    }
}

float ParameterUtils::feedbackNormalisedFromString(const juce::String& text)
{
    const float value = text.getFloatValue() / 100.0f;          // Normalise back to 0.0->1.0.

    if (value < PluginConfig::minFeedback)
    {
        return PluginConfig::minFeedback;
    }

    else if (value > PluginConfig::maxFeedback)
    {
        return PluginConfig::maxFeedback;
    }

    else if (value >= PluginConfig::minFeedback && value <= PluginConfig::maxFeedback)
    {
        return value;
    }

    else
    {
        return PluginConfig::defaultFeedback;
    }
}

float ParameterUtils::dryWetNormalisedFromString(const juce::String& text)
{
    const float value = text.getFloatValue() / 100.0f;          // Normalise back to 0.0->1.0.

    if (value < PluginConfig::minDryWet)
    {
        return PluginConfig::minDryWet;
    }

    else if (value > PluginConfig::maxDryWet)
    {
        return PluginConfig::maxDryWet;
    }

    else if (value >= PluginConfig::minDryWet && value <= PluginConfig::maxDryWet)
    {
        return value;
    }

    else
    {
        return PluginConfig::defaultDryWet;
    }
}


