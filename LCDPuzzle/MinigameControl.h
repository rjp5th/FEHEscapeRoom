#ifndef _MINIGAME_CONTROL_H
#define _MINIGAME_CONTROL_H

#include <Arduino.h>
#include <LiquidCrystal.h>

/*
 * Constant defines
 */

// Character Defines
#define UP_ARROW 0
#define DOWN_ARROW 1
#define RIGHT_ARROW 126
#define LEFT_ARROW 127

#define PLATFORM_CHAR 2
#define SMASH_CHAR 3
#define TL_BORDER_CHAR 4
#define BL_BORDER_CHAR 5
#define TR_BORDER_CHAR 6
#define BR_BORDER_CHAR 7
#define BORDER_CHAR 255


// IR Message Defines
#define DIGIT_0 0xE916FF00
#define DIGIT_1 0xF30CFF00
#define DIGIT_2 0xE718FF00
#define DIGIT_3 0xA15EFF00
#define DIGIT_4 0xF708FF00
#define DIGIT_5 0xE31CFF00
#define DIGIT_6 0xA55AFF00
#define DIGIT_7 0xBD42FF00
#define DIGIT_8 0xAD52FF00
#define DIGIT_9 0xB54AFF00

// Secret Password Sequence Length
#define SEQUENCE_LENGTH 6

/*
 * Game configuration defines
 */
// Width of game tiles
#define GAME_WIDTH 12
// Starting tick speed in ms
#define GAME_TICK_SPEED_DEFAULT 1000
// Minimum tick speed
#define GAME_TICK_SPEED_MIN 700
// Tick speed decrease rate
#define GAME_TICK_DECREASE_SPEED 20
// Maximum ticks (spaces) between digits being printed
#define GAME_ACTION_MAX_TICK 4
// Minimum ticks between clue showing
#define GAME_CLUE_COOLDOWN 3

// The probabilities are as 1/n, since it check is random(n)==0
// Probability of digit appearing on display
#define GAME_ACTION_PROBABILITY 4
// Probability of successful digit leading to clue showing (after cooldown)
#define GAME_CLUE_PROBABILITY 3

// Calculates the offset in display contents relative to the current display index
// Allows display shifting without needing to constantly shift portions of memory
#define DISP_REL_OFFSET(index) ((index+displayContentsOffset)%GAME_WIDTH)

// Game state constants
// Waiting for game to start by number press
#define GAME_STATE_PENDING_PRESS 0
// Displaying first frame frozen, waiting for user input
#define GAME_STATE_DISPLAY_FIRST_FRAME 1
// Game is actively being played
#define GAME_STATE_PLAYING 2
// Game is finished being played and now displaying end screen
#define GAME_STATE_END_SCREEN 3

/*
 * Class Declarations
 */
class MinigameControl{
  private:
    // Display variables
    LiquidCrystal* lcd;
    byte displayContents[GAME_WIDTH];
    int displayContentsOffset;

    // Game state variables
    int gameState;              // If the game is waiting for a button press before starting
    int passwordSequenceIndex;  // The index in the secret password sequence that should be displayed next
    int ticksSinceGenerate;     // Number of ticks since last number was generated on display
    int showClueCooldown;       // The number of ticks until clues can be generated
    long nextGameTick;          // The time in millis() of the next game tick (should prevent rollover problems)
    int tickSpeed;              // The duration of each tick in ms
    int pendingPress;           // The currently pending press in between ticks

    // Private methods
    // See method implementations for descriptions
    void redrawDisplay();
    bool shouldShowClue();
    void generateNextDisplayItem(bool disableGeneration);
    void endSequence(bool won);
    int getPendingPress();
  public:
    // Pubblic methods
    MinigameControl(LiquidCrystal* lcd);  // Initializes new MinigameControl class
    void startGameDisplayLoop();          // Initializes minigames and arduino to new game state
    void displayLoop();                   // Called to update the game logic
};

#endif
