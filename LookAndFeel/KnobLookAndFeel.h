/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 19 May 2024 2:13:37pm
    Author:  Luciano Muratore

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class KnobLookAndFeel: public juce::LookAndFeel_V4
{
public:
    KnobLookAndFeel() 
    {
        KnobImage = juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);
    }
    
    virtual ~KnobLookAndFeel() {}

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width,
        int height, float sliderPos, const float rotaryStartAngle,
        const float rotaryEndAngle, juce::Slider& slider) override
    {
        const int numFrames = KnobImage.getHeight() / KnobImage.getWidth();
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));

        const float radius = fmin(width * 0.5, height * 0.5);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;

        g.drawImage(KnobImage,
            rx,
            ry,
            2 * radius,
            2 * radius,
            0,
            frameIndex * knobImage.getWidth(),
            knobImage.getWidth(),
            knobImage.getWidth());

    }



private:
    juce::Image KnobImage;


};