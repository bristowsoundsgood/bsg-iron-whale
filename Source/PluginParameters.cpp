//
// Created by Joe Bristow on 14/11/2025.
//

#include "PluginParameters.h"
#include "../Utils/ParameterUtils.h"

PluginParameters::PluginParameters(const juce::AudioProcessorValueTreeState& stateManager)
{
    // Store the memory addresses of each parameter object upon construction.
    m_paramOutGain = dynamic_cast<juce::AudioParameterFloat*> (stateManager.getParameter(PluginConfig::paramIDOutGain.getParamID()));
    m_paramDelayTime = dynamic_cast<juce::AudioParameterFloat*> (stateManager.getParameter(PluginConfig::paramIDDelayTime.getParamID()));
    m_paramDryWet = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::paramIDDryWet.getParamID()));
}

// Sets the sample rate and ramp time for the parameter smoothers
void PluginParameters::prepare(const double sampleRate) noexcept
{
    m_smootherGain.reset(sampleRate, PluginConfig::rampSmoothTime);
    m_smootherDryWet.reset(sampleRate, PluginConfig::rampSmoothTime);
}

void PluginParameters::reset() noexcept
{
    // When playback restarts, set smoother values to the same value as the plugin parameters, meaning they do not have left-over interpolation.
    m_smootherGain.setCurrentAndTargetValue(m_paramOutGain->get());
    m_smootherDryWet.setCurrentAndTargetValue(m_paramDryWet->get());
}

void PluginParameters::update() noexcept
{
    m_smootherGain.setTargetValue(m_paramOutGain->get());
    m_smootherDryWet.setTargetValue(m_paramDryWet->get());
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout() noexcept
{
    return {
        std::make_unique<juce::AudioParameterFloat>(PluginConfig::paramIDOutGain, PluginConfig::paramNameOutGain, PluginConfig::minOutGain, PluginConfig::maxOutGain, PluginConfig::defaultOutGain),
        std::make_unique<juce::AudioParameterFloat>(PluginConfig::paramIDDelayTime, PluginConfig::paramNameDelayTime, PluginConfig::delayTimeRange,
            PluginConfig::defaultDelayTime, juce::AudioParameterFloatAttributes().withStringFromValueFunction(ParameterUtils::adaptPrecisionMilliseconds)),
        std::make_unique<juce::AudioParameterFloat>(PluginConfig::paramIDDryWet, PluginConfig::paramNameDryWet, PluginConfig::dryWetRange,
            PluginConfig::defaultDryWet)
    };
}
