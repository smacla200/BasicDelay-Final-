/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BasicDelayAudioProcessor::BasicDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{// Some feedback
    feedback = 0.5;
    
    // ¼ second delay
    delayTime = 0.25;
    
    // Start reading from the start of the circular buffer
    readIndex = 0;
    
    // Set the write index ahead of the read index
    writeIndex = delayTime;
    
    // Initial delay buffer size
    delayBufferLength = 0;
}

BasicDelayAudioProcessor::~BasicDelayAudioProcessor()
{
}

//==============================================================================
const String BasicDelayAudioProcessor::getName() const

{
    return JucePlugin_Name;
}
int BasicDelayAudioProcessor::getNumParameters()
{
    return kNumParameters;
}

float BasicDelayAudioProcessor::getParameter (int index)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case kDelayTimeParam: return delayTime;
        case kFeedbackParam: return feedback;
        default: return 0.0f;
    }
}

void BasicDelayAudioProcessor::setParameter (int index, float newValue)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case kDelayTimeParam:
            delayTime = newValue;
            // IMPORTANT: calculate the position of the readIndex relative to the write
            // i.e. the delay time in samples
            readIndex = (int)(writeIndex - (delayTime * delayBufferLength)
                              + delayBufferLength) % delayBufferLength;
            break;
        case kFeedbackParam:
            feedback = newValue;
            break;
        default:
            break;
    }
}

const String BasicDelayAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case kDelayTimeParam: return "delay time";
        case kFeedbackParam: return "feedback";
        default: break;
    }
    
    return String::empty;
}

const String BasicDelayAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

bool BasicDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double BasicDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String BasicDelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void BasicDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BasicDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // Maximum delay of 1 second
    delayBufferLength = (int)(sampleRate);
    
    // Set the buffer to 1 channel of the size of delayBufferLength using setSize
    delayBuffer.setSize(1, delayBufferLength);
    
    // Set all the samples in the buffer to zero
    delayBuffer.clear();
    
    // IMPORTANT: calculate the position of the read index relative to the write index
    // i.e. the delay time in samples
    readIndex = (int)(writeIndex - (delayTime * delayBufferLength)
                      + delayBufferLength) % delayBufferLength;
}

void BasicDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer&
                                             midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // channelData is an array of length numSamples which contain
    // the audio for one channel
    float *channelData = buffer.getWritePointer(0);
    
    // delayData is the circular buffer for implementing the delay
    float* delayData = delayBuffer.getWritePointer(0);
    
    // Set a wet mix level
    float wetMix = 0.5;
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        
        // Calculate the next output sample (current input sample + delayed version)
        float outputSample = (channelData[i] + (wetMix * delayData[readIndex]));
        
        // Write the current input into the delay buffer along with the delayed sample
        delayData[writeIndex] = channelData[i] + (delayData[readIndex] * feedback);
        // Increment the read index then check to see if it's greater than the buffer length
        // If so wrap back around to zero
        if (++readIndex >= delayBufferLength)
            readIndex = 0;
        // Same with write index
        if (++writeIndex >= delayBufferLength)
            writeIndex = 0;
        
        // Assign output sample computed above to the output buffer
        channelData[i] = outputSample;
    }
    
}

//==============================================================================
bool BasicDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BasicDelayAudioProcessor::createEditor()
{
    return new BasicDelayAudioProcessorEditor (*this);
}

//==============================================================================
void BasicDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicDelayAudioProcessor();
}
