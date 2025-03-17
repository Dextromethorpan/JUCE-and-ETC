/*
  ==============================================================================

    LFO.h
    Created: 5 May 2024 8:48:05pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class LFO
{
public:
    LFO();
    ~LFO();

    void setFrequencyValue(float rateValue);
    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);



private:
    float SampleRate{ 44100.0f };
    float twoPi{ juce::MathConstants<float>::twoPi };
    float frequency{ 0.0f };
    float time[2];
    float deltaTime[2];
};