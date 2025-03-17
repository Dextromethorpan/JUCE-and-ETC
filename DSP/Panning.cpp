/*
  ==============================================================================

    Panning.cpp
    Created: 5 May 2024 6:06:54pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#include "Panning.h"

Panning::Panning() {}
Panning::~Panning() {}

void Panning::setPanningValue(float inPanningValue)
{
    panningValue = inPanningValue;
}

void Panning::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);
            float pi=juce::

            //Left Channel
            if(channel == 0)
            {
                sample *= sqrtf(((pi / 2.0f) - panningValue) * (2.0f / pi) * (cosf(panningValue));
            }
            else
            {
                sample *= sqrtf(panningValue * (2.0f / pi) * sinf(panningValue));
            }

            buffer.setSample(channel, i, sample);

        }
    }
}