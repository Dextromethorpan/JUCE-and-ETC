/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel/KnobLookAndFeel.h"

//==============================================================================
/**
*/
class ProyectoCursoECT2402AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ProyectoCursoECT2402AudioProcessorEditor (ProyectoCursoECT2402AudioProcessor&);
    ~ProyectoCursoECT2402AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ProyectoCursoECT2402AudioProcessor& audioProcessor;
    juce::Slider volumenSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttach, paneoAttach, rateAttach, dryWetAttach;
    KnobLookAndFeel lookAndFeelKnob; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProyectoCursoECT2402AudioProcessorEditor)
};
