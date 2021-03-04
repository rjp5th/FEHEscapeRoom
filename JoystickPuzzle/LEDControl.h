#ifndef _LED_CONTROL_H
#define _LED_CONTROL_H

// Note: If these pins are redefined the enableBlinking caller must take that into account
// This is because the blinking uses timer pins, which are hardwired to pins 9 for A and 10 for B
#define BLUE_LED_PIN 8
#define RED_LED_PIN 9
#define GREEN_LED_PIN 10


// Bit 0: Red LED
// Bit 1: Green LED
// Bit 2: Blue LED
// Bit 3: Blinking
// Note, if blinking is set, the non-blinking lights are ignored

#define LED_BLINKING_FLAG (1<<3)

#define LED_STATE_OFF 0
#define LED_STATE_RED 1
#define LED_STATE_GREEN 2
#define LED_STATE_YELLOW 3
#define LED_STATE_BLUE 4

#define LED_STATE_RED_BLINKING  (LED_BLINKING_FLAG | LED_STATE_RED)
#define LED_STATE_GREEN_BLINKING  (LED_BLINKING_FLAG | LED_STATE_GREEN)
#define LED_STATE_YELLOW_BLINKING  (LED_BLINKING_FLAG | LED_STATE_YELLOW)

class LEDControl {
private:
    int ledState;
    void setLEDState(int state);
public:
    LEDControl();
    void displayIncorrect(bool enable);
    void displayCorrect(bool enable);
    void displayEntry(bool enable);
    void displayTimeout(bool enable);
};

#endif
