/*
==============================================================================
KOTempo.h
Created: 26 Sep 2022 3:51:21am
Author:  Penofcilin The King Of KO
Purpose: Provides useful tempo related methods, like getting the hertz values of notes. Make sure to set BPM and samplerate before using. 


hint you can easily find bpm in process block with following code:

(in processor header file)
KOTempo tempo;
juce::AudioPlayHead* playHead;
juce::AudioPlayHead::CurrentPositionInfo currentPosition;

(In processblock)
playHead = this->getPlayHead();
playHead->getCurrentPosition(currentPos);
tempo.setBPM(currentPos.bpm);
==============================================================================
*/

#pragma once
#ifndef KOTempo_h
#define KOTempo_h

#include <JuceHeader.h>

    #ifndef NOTE_TYPES_STRINGS 
    #define NOTE_TYPES_STRINGS  "Whole", "Half", "Dotted Half", "Quarter", "Dotted Quarter", "Triplet Quarter", "Eighth", "Dotted Eighth", "Triplet Eighth", "Sixteenth", "Dotted Sixteenth", "Triplet Sixteenth"
    #endif // !NOTE_TYPES_STRINGS 


class KOTempo
{
public:
    enum NoteTypes {Whole, Half, DottedHalf, Quarter, DottedQuarter, TripletQuarter, Eighth, DottedEighth, TripletEighth, Sixteenth, DottedSixteenth, TripletSixteenth};
    void setBPM(float bpm);
    void setSampleRate(float samplerate);
    juce::StringArray getNoteTypes();
    juce::StringArray getStraightNoteTypes();
    juce::StringArray getModdedNoteTypes();

    //These will return the length of a given note, either in hz, samples or milliseconds
    float getNoteLengthHertz(NoteTypes type);
    float getNoteLengthSamples(NoteTypes type);
    float getNoteLengthMS(NoteTypes type);

private:
    float BPM;
    float sampleRate;
};
#endif // !KOTempo_h
