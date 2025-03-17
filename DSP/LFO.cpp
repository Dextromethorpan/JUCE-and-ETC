/*
  ==============================================================================

    LFO.cpp
    Created: 5 May 2024 8:48:05pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#include "LFO.h"

LFO::LFO() {}
LFO::~LFO() {}

void LFO::setFrequencyValue(float rateValue)
{
    frequency = rateValue;

}


void LFO::prepare(double theSampleRate)
{
    SampleRate =static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / SampleRate; 
    }

}

void LFO::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);

            //y=0.5*sin(2pi*ft)*x+0.5
            float sinValue = (0.5f * sinf(twoPi * frequency * time[channel])) + 0.5f;

            float outSample = inSample * sinValue;

            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];
        }
    }




}