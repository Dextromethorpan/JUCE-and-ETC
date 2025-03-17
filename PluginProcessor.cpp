/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ProyectoCursoECT2402AudioProcessor::ProyectoCursoECT2402AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),apvts(*this,nullptr, "Parameters",createParameters())
#endif
{
}

ProyectoCursoECT2402AudioProcessor::~ProyectoCursoECT2402AudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ProyectoCursoECT2402AudioProcessor::createParameters()
{
    float pi = juce::MathConstants<float>::pi;
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    /*
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "SliderFloat",1 }, "SliderFloat", 0.0f, 100.0f, 80.0f));
    parameters.add(std::make_unique<juce::AudioParameterInt>(juce::ParameterID{ "SliderInt",1 }, "SliderFloat", 0, 100, 50));
    parameters.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID{ "Button",1 }, "Button", true));
    parameters.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{ "Options",1 }, "Options", juce::StringArray{"1/2","1/4","1/8","1/16"},2));
    */

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Volume", 1), "Volume", 0.0f,2.0f, 1.0f)); 
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Panning", 1), "Panning", 0.0f, pi/2.0f, pi/4.0f));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Rate", 1), "Rate", 0.0f, 20.0f, 3.0));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("LFOState", 1), "LFOState", "true"));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("DryWet", 1), "DryWet", 0.0f,100.0f,50.0f));
    parameters.add(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID("LFOChoice", 1), "LFOChoice",
        juce::StringArray("Sine", "Square", "Saw", "Triangle"), 0));

    return parameters;
}


//==============================================================================
const juce::String ProyectoCursoECT2402AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProyectoCursoECT2402AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoCursoECT2402AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProyectoCursoECT2402AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ProyectoCursoECT2402AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProyectoCursoECT2402AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ProyectoCursoECT2402AudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProyectoCursoECT2402AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ProyectoCursoECT2402AudioProcessor::getProgramName (int index)
{
    return {};
}

void ProyectoCursoECT2402AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ProyectoCursoECT2402AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    //SamplesperBlock = buffer size


    lfo.prepare(sampleRate);
    biquad.prepare(sampleRate);
    biquad.setFrequency(1000.0f);
    biquad.setQ(0.71f);
    //Filter
    juce::dsp::ProcessSpec inSpec;
    inSpec.sampleRate = sampleRate;
    inSpec.maximumBlockSize = samplesPerBlock;
    inSpec.numChannels = getTotalNumOutputChannels();

    BandPassFilter.prepare(inSpec);


}

void ProyectoCursoECT2402AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProyectoCursoECT2402AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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
#endif

void ProyectoCursoECT2402AudioProcessor::updateParameters()
{
    float inVolumeParameter = *apvts.getRawParameterValue("Volume");
    float inPanningParameter = *apvts.getRawParameterValue("Panning");
    volume.setVolumeValue(inVolumeParameter);
    panning.setPanningValue(inPanningParameter);
    float inRateParameter = *apvts.getRawParameterValue("Rate");
    bool inLFOStateParameter= *apvts.getRawParameterValue("LFOState");
    lfo.setFrequencyValue(inRateParameter);
    lfoState = inLFOStateParameter;
    float inDryWetParameter= *apvts.getRawParameterValue("DryWet");
    dryWet.setDryWetValue(inDryWetParameter);

}





void ProyectoCursoECT2402AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    /*
    for (int channel = 0; channel < buffer.getNumSamples(); ++channel)
    {
        for (int i= 0; i< buffer.getNumSamples(); ++i)
        {
            auto inSample = buffer.getSample(channel, i);
            float processedSample = inSample * 0.5f;
            buffer.setSample(channel, i, processedSample);
        }
    }
   */
    updateParameters();
    
    volume.process(buffer);
    panning.process(buffer);

    if (lfoState) {
        lfo.process(buffer);
    }

    biquad.process(buffer);


    dryBuffer.makeCopyOf(buffer);
    dryWet.process(dryBuffer, buffer);
    BandPassFilter.processBandPass(buffer);
    LowPassFilter.processLowPass(buffer);


}

//==============================================================================
bool ProyectoCursoECT2402AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ProyectoCursoECT2402AudioProcessor::createEditor()
{
    //return new ProyectoCursoECT2402AudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);


}

//==============================================================================
void ProyectoCursoECT2402AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<juce::XmlElement> xml(apvts.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void ProyectoCursoECT2402AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(apvts.state.getType()))
        {
            auto state = juce::ValueTree::fromXml(*xmlState);
            apvts.replaceState(state);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProyectoCursoECT2402AudioProcessor();
}
