/*
  ==============================================================================

    KOLFO.cpp
    Created: 5 Dec 2022 6:29:02pm
    Author:  Levi

  ==============================================================================
*/

#include "KOLFO.h"
//There are two of these because you need to set the sampleRate to the frequency with which you'll be accessing the LFO.
//If you're just doing it in your regular process block, define sampleRate to be your samplerate / buffersize
//If you're gonna be processing it within the buffer/sample loop, just give it a regular spec
void  KOLFO::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate / spec.maximumBlockSize;
    reset();
}

void  KOLFO::prepare(const float customSampleRate)
{
    sampleRate = customSampleRate;

    reset();
}

void  KOLFO::reset()
{
    phase.reset();
}

//Set Wave Function for Lfo
void  KOLFO::initialise(const std::function<float(float)>& function,
                        size_t lookupTableNumPoints)
{
    if (lookupTableNumPoints != 0)
    {
        auto* table = new juce::dsp::LookupTableTransform<float>(function, -juce::MathConstants<float>::pi, juce::MathConstants<float>::pi,
                                                                 lookupTableNumPoints);

        lookupTable.reset(table);
        generator = [table](float x) { return (*table) (x); };
    }
    else
    {
        //This one is the part that I use, simply sets the wavefunction to whatever function is passed as arg
        generator = function;
    }
}

//Returns a number between -1 and 1.
float  KOLFO::getNextValue()
{
    auto increment = juce::MathConstants<float>::twoPi * NormalizedFrequency;
    return generator(phase.advance(increment) - juce::MathConstants<float>::pi);
}

void  KOLFO::setParameter(ParameterId parameter, float parameterValue)
{
    switch (parameter)
    {
    case  KOLFO::ParameterId::Frequency: m_frequency = parameterValue; NormalizedFrequency = parameterValue / sampleRate; break;
    case  KOLFO::ParameterId::Bypass: m_GlobalBypass = static_cast<bool>(parameterValue); break;
    }
}

float  KOLFO::getFrequency()
{
    return m_frequency;
}

void  KOLFO::setWaveType(WaveType newWaveType)
{
    switch (newWaveType)
    {
    case  KOLFO::WaveType::Sine:
    {
        initialise([](float x) {return std::sin(x); });
        break;
    }
    case  KOLFO::WaveType::Saw:
    {
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;
    }
    case  KOLFO::WaveType::SawDown:
    {
        initialise([](float x) {return (x / juce::MathConstants<float>::pi) * (-1); });
        break;
    }
    case  KOLFO::WaveType::Square:
    {
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
        break;
    }
    case  KOLFO::WaveType::Random: //Work in progress, may or may not work idk
    {
        initialise([&](float x) {return (x * rando.nextFloat()); });
    }
    }
}