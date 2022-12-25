/*
  ==============================================================================
    KOLFO.H
    Created: 26 Sep 2022
    Author:  Penofcilin, King of KO Audio
    Purpose: Provides a useful LFO class for use within a JUCE process block.
    Adapted from Viator DSP's LFOGenerator Module:
  ==============================================================================
*/


#pragma once
#ifndef KOLFO_h
#define KOLFO_h

#include <JuceHeader.h>

class KOLFO
{
public:

    void prepare(const juce::dsp::ProcessSpec& spec);

    void prepare(const float customSampleRate);

    void reset();

    

    float getNextValue();

    enum class WaveType
    {
        Sine,
        Saw,
        SawDown,
        Square,
        //Random
    };

    void setFrequency(float newFrequency);
    float getFrequency();
    void setWaveType(WaveType newWaveType);

private:

    float m_frequency;
    float sampleRate;
    float NormalizedFrequency;

    juce::Random rando;

    juce::dsp::Phase<float> phase;

    void initialise(const std::function<float(float)>& function);
    std::function<float(float)> generator;
}; 

#endif /* KOLFO*/
