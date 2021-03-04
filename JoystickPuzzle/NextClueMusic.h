#ifndef _NEXT_CLUE_MUSIC_H
#define _NEXT_CLUE_MUSIC_H

#include <Arduino.h>

class NextClueMusic {
public:
    NextClueMusic() {}
    void playSuccess();
    void playFailure();
    void playEntryChirp();
    void playTimeoutChirp();
};

#endif
