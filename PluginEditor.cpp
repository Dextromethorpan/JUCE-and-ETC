/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProyectoCursoECT2402AudioProcessorEditor::ProyectoCursoECT2402AudioProcessorEditor (ProyectoCursoECT2402AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    volumenSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(volumenSlider);
    volumenSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumenSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour(255, 255, 255));
    volumenSlider.setLookAndFeel(&lookAndFeelKnob);
    volumenAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"Volume",volumenSlider);

    setSize (400, 300);
}

ProyectoCursoECT2402AudioProcessorEditor::~ProyectoCursoECT2402AudioProcessorEditor()
{
    volumenSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void ProyectoCursoECT2402AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ProyectoCursoECT2402AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    volumenSlider.setBounds(0,0,100,100);
}
