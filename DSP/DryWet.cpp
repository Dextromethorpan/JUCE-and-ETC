/*
  ==============================================================================

    DryWet.cpp
    Created: 6 May 2024 12:51:02pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#include "DryWet.h"

DryWet::DryWet() {}
DryWet::~DryWet() {}

void DryWet::setDryWetValue(float theDryWetValue)
{
    dryWetValue = theDryWetValue/100.0f;
}

void DryWet::process(juce::AudioBuffer<float>& drybuffer, juce::AudioBuffer<float>& wetbuffer)
{
    for (int channel = 0; channel < drybuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < drybuffer.getNumSamples(); i++)
        {
            float wetSample = wetbuffer.getSample(channel, i);
            float drySample = drybuffer.getSample(channel, i);

            float outSample = drySample * (1 - dryWetValue) + (wetSample * dryWetValue);

            wetbuffer.setSample(channel, i, outSample);

        }
    }
}