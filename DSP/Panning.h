/*
  ==============================================================================

    Panning.h
    Created: 5 May 2024 6:07:02pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Panning
{
public:
    Panning();
    ~Panning();

    void setPanningValue(float inPanningValue);
    void process(juce::AudioBuffer<float>& buffer);


private:
    float pi{ juce::MathConstants<float>::pi };
    float panningValue{ juce::MathConstants<float>::pi / 4.0f };


};