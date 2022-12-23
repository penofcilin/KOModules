/*
==============================================================================
KOTempo.h
Created: 26 Sep 2022 3:51:21am
Author:  Penofcilin The King Of KO
Purpose: Provides useful tempo related methods, like getting the hertz values of notes
==============================================================================
*/

#pragma once
#ifndef KOTempo_h
#define KOTempo_h

#include <JuceHeader.h>
class KOTempo
{
public:
    enum NoteTypes {Whole, Half, DottedHalf, Quarter, DottedQuarter, TripletQuarter, Eighth, DottedEighth, TripletEighth, Sixteenth, DottedSixteenth, TripletSixteenth};
    void prepare(float bpm);
    void prepare(float bpm, float samplerate);
    juce::StringArray getNoteTypes();
    juce::StringArray getStraightNoteTypes();
    juce::StringArray getModdedNoteTypes();

    //These will return the length of a given note, either in hz, or samples
    float getNoteLengthHertz(NoteTypes type);
    float getNoteLengthSamples(NoteTypes type);
    float getNoteLengthMS(NoteTypes type);

private:
    float BPM;
    float sampleRate;
};
#endif // !KOTempo_h
