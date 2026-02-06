#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginProcessor::DelayPluginProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),  stateManager(*this, nullptr, "parameters", PluginParameters::createParameterLayout()), params(stateManager)
{
}

DelayPluginProcessor::~DelayPluginProcessor()
{
}

//==============================================================================
const juce::String DelayPluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayPluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayPluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayPluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayPluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayPluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayPluginProcessor::getCurrentProgram()
{
    return 0;
}

void DelayPluginProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String DelayPluginProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void DelayPluginProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void DelayPluginProcessor::prepareToPlay (const double sampleRate, const int samplesPerBlock)
{
    const int numChannels { getTotalNumOutputChannels() };

    // Parameters
    params.prepare(sampleRate);
    params.reset();

    delayDSP.prepareToPlay(numChannels, static_cast<float>(sampleRate), samplesPerBlock);
}

void DelayPluginProcessor::releaseResources()
{
    // When playback stops, free up memory.
}

bool DelayPluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto mono { juce::AudioChannelSet::mono() };
    const auto stereo { juce::AudioChannelSet::stereo() };
    const auto mainIn { layouts.getMainInputChannelSet() };
    const auto mainOut { layouts.getMainOutputChannelSet() };

    if (mainIn == mono && mainOut == mono) { return true; }
    if (mainIn == mono && mainOut == stereo) { return true; }
    if (mainIn == stereo && mainOut == stereo) { return true; }

    return false; // e.g., input = stereo, output = mono.
}

void DelayPluginProcessor::processBlock (juce::AudioBuffer<float>& audioBuffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    juce::ScopedNoDenormals noDenormals;

    const int totalNumInputChannels = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    /* Handles mono tracks in host. If an input/output is mono, this creates two channels, L and R, with the same signal.
     * Therefore,  no DSP logic needs changing: it can treat a signal as stereo.
     */
    const auto mainInput { getBusBuffer(audioBuffer, true, 0) };
    const auto mainInputChannels { mainInput.getNumChannels() };
    const auto isMainInputStereo { mainInputChannels > 1 };
    const float* inputDataL { mainInput.getReadPointer(0) };
    const float* inputDataR { mainInput.getReadPointer(isMainInputStereo ? 1 : 0) };

    const auto mainOutput { getBusBuffer(audioBuffer, false, 0) };
    const auto mainOutputChannels { mainOutput.getNumChannels() };
    const auto isMainOutputStereo { mainOutputChannels > 1 };
    float* outputDataL { mainOutput.getWritePointer(0) };
    float* outputDataR { mainOutput.getWritePointer(isMainOutputStereo ? 1 : 0) };

    const int blockSize = audioBuffer.getNumSamples();

    // Clears any output channels that do not contain input data. Prevents screaming feedback.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        audioBuffer.clear (i, 0, audioBuffer.getNumSamples());
    }

    // Before DSP...
    params.update();
    const float delayTime { params.getDelayTimeSeconds() };
    const float feedback { params.getFeedback() };
    const float dryWet { params.getDryWet() };
    const bool isPingPong { params.getPingPongToggle() };
    const float stereoWidth { params.getStereoWidth() };
    const float outGain { params.getOutputGainDB() };

    delayDSP.setDryWet(dryWet);
    delayDSP.setFeedback(feedback);
    delayDSP.setTargetDelayTime(delayTime);
    widthDSP.setWidth(stereoWidth);
    gainDSP.setGainDB(outGain);

    // DSP
    delayDSP.processBlock(audioBuffer, blockSize, isPingPong);
    widthDSP.processBlock(audioBuffer, blockSize);
    gainDSP.processBlock(audioBuffer, blockSize);
}

//==============================================================================
bool DelayPluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DelayPluginProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void DelayPluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    copyXmlToBinary(*stateManager.copyState().createXml(), destData);
}

void DelayPluginProcessor::setStateInformation (const void* data, const int sizeInBytes)
{
    const std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName(stateManager.state.getType()))
    {
        stateManager.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayPluginProcessor();
}

juce::AudioProcessorValueTreeState& DelayPluginProcessor::getProcessorValueTreeState()
{
    return stateManager;
}

