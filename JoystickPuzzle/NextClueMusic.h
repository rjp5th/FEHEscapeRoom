#ifndef _NEXT_CLUE_MUSIC_H
#define _NEXT_CLUE_MUSIC_H

class NextClueMusic {
public:
    NextClueMusic() {}
    void playSuccess();
    void playFailure();
    void playEntryChrip();
private:
    Tone tone; 
};

#endif
