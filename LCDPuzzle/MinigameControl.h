#ifndef _MINIGAME_CONTROL_H
#define _MINIGAME_CONTROL_H

class MinigameControl{
  private:
    LiquidCrystal* lcd;
  public:
    MinigameControl(LiquidCrystal* lcd);
    void startGameDisplayLoop();
    void displayLoop();
};

#endif
