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
void DelayPluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int numChannels = getTotalNumOutputChannels();

    // Parameters
    params.prepare(sampleRate);
    params.reset();

    // Prepare DSP objects. One per output channel
    gainDSP.resize(numChannels);
    delayDSP.resize(numChannels);

    for (auto& d : delayDSP)
    {
        d.prepareToPlay(numChannels, static_cast<float>(sampleRate), samplesPerBlock);
    }
}

void DelayPluginProcessor::releaseResources()
{
    // When playback stops, free up memory.
}

bool DelayPluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}

void DelayPluginProcessor::processBlock (juce::AudioBuffer<float>& audioBuffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    juce::ScopedNoDenormals noDenormals;

    const int totalNumInputChannels = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    const int blockSize = audioBuffer.getNumSamples();

    // Clears any output channels that do not contain input data. Prevents screaming feedback.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        audioBuffer.clear (i, 0, audioBuffer.getNumSamples());
    }

    // Before DSP...
    params.update();
    const float outGain = params.getOutputGainDB();
    const float delayTime = params.getDelayTimeSeconds();
    const float dryWet = params.getDryWetNormalised();

    for (auto& g : gainDSP) g.setGainDB(outGain);
    for (auto& d : delayDSP)
    {
        d.setDryWet(dryWet);
        d.setTargetDelayTime(delayTime);
    }

    // Process blocks of samples
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = audioBuffer.getWritePointer(channel);

        delayDSP[channel].processBlock(channel, channelData, blockSize);
        gainDSP[channel].processBlock(channelData, blockSize);
    }
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

