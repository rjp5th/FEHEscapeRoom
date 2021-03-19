#include "MinigameControl.h"

/*
 * External defines
 */
// IRremote.h references in LCDPuzzle.ino since it can't be included in multiple cpp files
extern bool ir_data_available();
extern unsigned long ir_get_data();
extern void ir_resume();

/*
 * Array Declarations
 */

// Character Data
byte upArrowChar[] = {0x00, 0x04, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x00};
byte downArrowChar[] = {0x00, 0x04, 0x04, 0x04, 0x15, 0x0E, 0x04, 0x00};
byte platformChar[] = {0x1F, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x04, 0x04};
byte smashChar[] = {0x05, 0x04, 0x14, 0x05, 0x04, 0x1F, 0x1F, 0x1F};
byte tlBorderChar[] = {0x1F, 0x1F, 0x1E, 0x1E, 0x1C, 0x1C, 0x18, 0x18};
byte blBorderChar[] = {0x18, 0x18, 0x1C, 0x1C, 0x1E, 0x1E, 0x1F, 0x1F};
byte trBorderChar[] = {0x1F, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x03, 0x03};
byte brBorderChar[] = {0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F};

// Digit Mappings
unsigned long digits[10] = {DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_8, DIGIT_9};

// Secret Password Sequence
//extern byte *arrow_password_sequence;
byte arrow_password_sequence[SEQUENCE_LENGTH] = {UP_ARROW, UP_ARROW, DOWN_ARROW, DOWN_ARROW, LEFT_ARROW, RIGHT_ARROW};

/*
 * Class Constructor. Just receives lcd variable for later use
 */
MinigameControl::MinigameControl(LiquidCrystal* lcd) {
  this->lcd = lcd;
}

/*
 * Redraws the display in game state
 */
void MinigameControl::redrawDisplay(){
  lcd->clear();
  lcd->home();
  // Draw border
  lcd->write(BORDER_CHAR);
  lcd->write(byte(TL_BORDER_CHAR));

  // Draw game area
  for (int i = 0; i < GAME_WIDTH; i++){
    lcd->write(displayContents[DISP_REL_OFFSET(i)]);
  }

  // Draw end border
  lcd->write(byte(TR_BORDER_CHAR));
  lcd->write(BORDER_CHAR);

  // Draw bottom part of screen
  lcd->setCursor(0,1);
  lcd->write(BORDER_CHAR);
  lcd->write(byte(BL_BORDER_CHAR));
  lcd->write(byte(PLATFORM_CHAR));

  // Draw last bottom border
  lcd->setCursor(14,1);
  lcd->write(byte(BR_BORDER_CHAR));
  lcd->write(BORDER_CHAR);
}

/*
 * Initializes arduino and class into a state that displayLoop can be called
 * Initializes the game to reset and configures the lcd and rng
 */
void MinigameControl::startGameDisplayLoop() {
  // Initialize LCD
  lcd->createChar(UP_ARROW, upArrowChar);
  lcd->createChar(DOWN_ARROW, downArrowChar);
  lcd->createChar(PLATFORM_CHAR, platformChar);
  lcd->createChar(SMASH_CHAR, smashChar);
  lcd->createChar(TL_BORDER_CHAR, tlBorderChar);
  lcd->createChar(BL_BORDER_CHAR, blBorderChar);
  lcd->createChar(TR_BORDER_CHAR, trBorderChar);
  lcd->createChar(BR_BORDER_CHAR, brBorderChar);
  lcd->clear();
  lcd->home();
  lcd->print("==Press Number==");
  lcd->setCursor(0,1);
  lcd->print("  ==To Begin==  ");

  //Seed RNG
  randomSeed(analogRead(0));

  // Reset game state  
  passwordSequenceIndex = 0;                  // Reset entered password
  ticksSinceGenerate = GAME_ACTION_MAX_TICK;  // Force the first item generated to be a press
  showClueCooldown = GAME_CLUE_COOLDOWN;      // Set game clue cooldown to default value
  pendingPress = -1;                          // Clear any pending presses
  tickSpeed = GAME_TICK_SPEED_DEFAULT;        // Set the tick speed to starting speed
  gameState = GAME_STATE_PENDING_PRESS;       // Set the game state to launch screen
  nextGameTick = millis();                    // Set the next game tick to start immediately

  // Generate a game field
  displayContentsOffset = 0;
  for (int i = 0; i < GAME_WIDTH; i++){
    bool disableGeneration = false;
    if (i == 1 || i == 2){
      disableGeneration = true;
    }
    displayContentsOffset = (displayContentsOffset+1)%GAME_WIDTH;
    generateNextDisplayItem(disableGeneration);
  }
}

/*
 * Generates the next item to appear on the display, either digit or space
 * Determined using RNG and game state
 * Disable generation will force the block to be clear. Used during game start
 */
void MinigameControl::generateNextDisplayItem(bool disableGeneration) {
  if (!disableGeneration && (ticksSinceGenerate >= GAME_ACTION_MAX_TICK || random(GAME_ACTION_PROBABILITY) == 0)) {
    ticksSinceGenerate = 0;
    // Set display to random character between 0 and 9
    displayContents[DISP_REL_OFFSET(GAME_WIDTH-1)] = '0' + random(10);
  } else {
    ticksSinceGenerate++;
    displayContents[DISP_REL_OFFSET(GAME_WIDTH-1)] = ' ';
  }
}

/*
 * Checks if the code should show a clue
 * Note that by calling this class it updates the state for clue cooldowns
 */
bool MinigameControl::shouldShowClue() {
  if (showClueCooldown > 0){
    showClueCooldown--;
  } else {
    if (random(GAME_CLUE_PROBABILITY) == 0) {
      showClueCooldown = GAME_CLUE_COOLDOWN;
      return true;
    }
  }
  return false;
}

/*
 * Gets a pending button press from the IR receiver
 * Returns as an int of the digit pressed
 */
int MinigameControl::getPendingPress() {
  int pendingPress = -1;
  if (ir_data_available()){
    if (ir_get_data() != 0) {
      unsigned long data = ir_get_data();
      for (int i = 0; i < 10; i++){
        if (data == digits[i]){
          pendingPress = i;
        }
      }
    }
    ir_resume();
  }
  return pendingPress;
}

/*
 * Displays an ending message depending on win or lose
 * Resets the game to its default state
 * The displayLoop code should return immediately after calling this
 */
void MinigameControl::endSequence(bool won) {
  lcd->clear();
  lcd->home();
  if (won) {
    lcd->print(" ===YOU WON!===");
  } else {
    lcd->print("===GAME OVER!===");
  }
  gameState = GAME_STATE_END_SCREEN;
  nextGameTick = millis() + 5000;
}

/*
 * The main game loop code
 * Responsible for managing the game while it is running
 */
void MinigameControl::displayLoop() {
  if (gameState == GAME_STATE_PENDING_PRESS) {
    if (getPendingPress() != -1){
      this->redrawDisplay();
      gameState = GAME_STATE_DISPLAY_FIRST_FRAME;
    }
    return;
  } else if (gameState == GAME_STATE_DISPLAY_FIRST_FRAME) {
    int entry = getPendingPress();
    if ((entry + '0') == displayContents[DISP_REL_OFFSET(0)]){
      pendingPress = entry;
      lcd->setCursor(2, 0);
      lcd->write(byte(SMASH_CHAR));
      nextGameTick = millis() + tickSpeed;
      gameState = GAME_STATE_PLAYING;
    }
  } else if (gameState == GAME_STATE_PLAYING) {
    if (nextGameTick <= millis()) {
      nextGameTick = millis() + tickSpeed;
  
      // Check if there was supposed to be a press and there wasn't one
      if (displayContents[DISP_REL_OFFSET(0)] != ' ' && pendingPress == -1) {
        this->endSequence(false);
        return;
      }
      pendingPress = -1;
  
      displayContentsOffset = (displayContentsOffset+1)%GAME_WIDTH;
      this->generateNextDisplayItem(false);
      this->redrawDisplay();
    }
  
    // Do processing on input
    int entry = getPendingPress();
    if (entry != -1 && pendingPress == -1){
      pendingPress = entry;
      if ((pendingPress + '0') != displayContents[DISP_REL_OFFSET(0)]) {
        this->endSequence(false);
      } else {
        // This is the code that runs on a successful input
  
        // Speed up game
        if ((tickSpeed-GAME_TICK_DECREASE_SPEED) > GAME_TICK_SPEED_MIN) {
          tickSpeed -= GAME_TICK_DECREASE_SPEED;
        } else {
          tickSpeed = GAME_TICK_SPEED_MIN;
        }
  
        // Flash a clue if it should
        lcd->setCursor(2, 0);
        if (this->shouldShowClue()){
          lcd->write(byte(arrow_password_sequence[passwordSequenceIndex]));
          passwordSequenceIndex++;
          if (passwordSequenceIndex == SEQUENCE_LENGTH){
            delay(tickSpeed);
            this->endSequence(true);
          }
        } else {
          lcd->write(byte(SMASH_CHAR));
        }
      }
    }
  }
  else if (gameState == GAME_STATE_END_SCREEN) {
    if (nextGameTick <= millis()) {
      // Clear any presses that might have happened accidentally
      this->getPendingPress();
      this->startGameDisplayLoop();
    }
  }
}
