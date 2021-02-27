#ifndef _JOYSTICK_PASSCODE_H
#define _JOYSTICK_PASSCODE_H


#define UP_PRESS 1
#define DOWN_PRESS 2
#define LEFT_PRESS 3
#define RIGHT_PRESS 4
#define CLICK_PRESS 5

#define SEQUENCE_SIZE 6

const int validSequence[SEQUENCE_SIZE] = {UP_PRESS, UP_PRESS, DOWN_PRESS, DOWN_PRESS, LEFT_PRESS, RIGHT_PRESS};

class JoystickPasscode {
private:
    int inputSequence[SEQUENCE_SIZE];
    int sequenceIndex;

public:
    void waitAndProcessAction();
    bool sequenceCompleted();
    bool sequenceCorrect();
    void resetSequence();
}

#endif
