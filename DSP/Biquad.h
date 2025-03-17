/*
  ==============================================================================

    Biquad.h
    Created: 6 May 2024 3:42:03pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Biquad
{
public:
    
    Biquad();
    ~Biquad();
    
    void prepare (double inSampleRate); //para frequencia de sampleo
    
    void process (juce::AudioBuffer<float> inBuffer);
    
    float processSample (float inSample, int channel);
    
    void setFrequency (float inFrequency);
    
    void setQ (float inQ);
    
    void updateFilter();
    
private:
    
    double sampleRate {0.0f};
    
    float x1[2] = {0.0f};
    float x2[2] = {0.0f};
    float y1[2] = {0.0f};
    float y2[2] = {0.0f};
    
    float w0 {0.0f};
    float alpha {0.0f};
    
    float b0 {0.0f};
    float b1 {0.0f};
    float b2 {0.0f};
    float a0 {0.0f};
    float a1 {0.0f};
    float a2 {0.0f};
    
    float frequency {1000.0f};
    float Q {0.71f};
};