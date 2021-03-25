#ifndef _NEXT_CLUE_MUSIC_H
#define _NEXT_CLUE_MUSIC_H

#include <Arduino.h>

#define BUZZER_PIN 11

class NextClueMusic {
public:
    NextClueMusic() {}
    void playSuccess();
    void playFailure();
    void playEntryChirp();
    void playTimeoutChirp();
};

#endif
