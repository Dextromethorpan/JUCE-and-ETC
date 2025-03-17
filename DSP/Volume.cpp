/*
  ==============================================================================

    Volume.cpp
    Created: 30 Apr 2024 8:57:04pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#include "Volume.h"

Volume::Volume() {}
Volume::~Volume() {}

void Volume::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float processedSample = inSample * volumeValue;
            buffer.setSample(channel, i, processedSample);
        }
    }

}

void Volume::setVolumeValue(float inVolumeValue)
{
    volumeValue = inVolumeValue;
}