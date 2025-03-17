/*
  ==============================================================================

    DryWet.h
    Created: 6 May 2024 12:51:02pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class DryWet
{

public:
    DryWet();
    ~DryWet();

    void setDryWetValue(float dryWetValue);
    void process(juce::AudioBuffer<float>& drybuffer,juce::AudioBuffer<float>&wetbuffer);

private:
    float dryWetValue;
};