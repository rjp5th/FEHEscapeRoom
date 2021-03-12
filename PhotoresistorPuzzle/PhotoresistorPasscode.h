#ifndef _PHOTORESISTOR_PASSCODE_H
#define _PHOTORESISTOR_PASSCODE_H

#include <Arduino.h>

#define PIN_COUNT 6

// Threshold at which the photoresistor registers darkness and a note press
const uint16_t threshold_values[PIN_COUNT] = {50, 100, 100, 200, 150, 75};

#define TONE_DURATION 500

/*
 * Pin Defines
 */
#define BUZZER_PIN 11
#define RESET_PIN 10

// Index of pinMappings corresponds to note constants defined below
const uint8_t analogPinMappings[PIN_COUNT] = {A0, A1, A2, A3, A4, A5};

// Port D corresponds to Pins 0-7 on Arduino, mask selects pins 2-7
// Pins 2-7 corresponds note constant defines + 2
#define SEVEN_SEGMENT_PORT PORTD
#define SEVEN_SEGMENT_DIR DDRD
#define SEVEN_SEGMENT_MASK 0b11111100

/*
 * Note Constant Defines
 */
#define CL_NOTE 0
#define D_NOTE 1
#define E_NOTE 2
#define G_NOTE 3
#define A_NOTE 4
#define CH_NOTE 5

#define NOTE_C7  2093
#define NOTE_D7  2349
#define NOTE_E7  2637
#define NOTE_G7  3136
#define NOTE_A7  3520
#define NOTE_C8  4186
const int toneMapping[PIN_COUNT] = {NOTE_C7, NOTE_D7, NOTE_E7, NOTE_G7, NOTE_A7, NOTE_C8};

/*
 * Sequence Defines
 */
const int validSequence[PIN_COUNT] = {E_NOTE, D_NOTE, CL_NOTE, A_NOTE, G_NOTE, CH_NOTE};

/*
 * Data Type Defines
 */
union entered_notes {
  struct note_bitfield {
    uint8_t : 2, cl_note :1, d_note :1, e_note :1, g_note :1, a_note :1, ch_note :1;
  } notes;
  uint8_t pin_value;
};

class PhotoresistorPasscode {
  private:
    int inputSequence[PIN_COUNT];
    int sequenceIndex;
    union entered_notes enteredNotes;
    void resetSequence();

  public:
    PhotoresistorPasscode();
    void updateState();
    bool sequenceCompleted();
    bool sequenceCorrect();
};

#endif
