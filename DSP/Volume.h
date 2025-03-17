/*
  ==============================================================================

    Volume.h
    Created: 30 Apr 2024 8:57:04pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Volume
{
public:
    Volume();
    ~Volume();

    void setVolumeValue(float inVolumeValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float volumeValue{ 1.0f };
};

