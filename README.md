# FEH Escape Room Microcontroller Code
This repository contains the Arduino code for the microcontrollers used in FEH 1282.01 Team 42's Escape Room.

## JoystickPuzzle
Code for the Joystick Puzzle. This puzzle will play a series of tones which is the clue for the next puzzle, the Photoresistor Puzzle, when the correct sequence of inputs is entered on the joystick. The sequence of inputs for this puzzle is given in the LCD Puzzle.

This code requires the following elements:
* Joystick
* Piezoelectric Buzzer
* RGB LED

## LCDPuzzle
Code for the LCD & IR Puzzle. This puzzle is designed to be a divider from the first half and the second half of the puzzle sequence. This will require the codes given from the Thermistoor Puzzle, Block Fitting Puzzle, and Sudoku Password to continue in the puzzle. A game will then begin, and it will reveal arrow sequences as it is completed as the clues for the Joystick Puzzle.

This code requires the following elements:
* 16x2 LCD
* IR Receiver

## PhotoresistorPuzzle
Code for the Photoresistor Puzzle. This puzzle will open a door with a Servo motor to give the key to the treasure chest when the right tone sequence is entered on the photoresistor "keyboard". The correct sequence of tones is given by the success tone played by the JoystickPuzzle.

This code requires the following elements:
* 7 Segment Display
* Servo Motor
* 6 Photoresistors
* Piezoelectric Buzzer
* Push Button

## ThermistorPuzzle
Code for the Thermistor Puzzle. This puzzle will reveal a 4 digit clue which is a required password for the LCD Puzzle when the thermistor goes above the ambient temperature by a defined amount from a finger being placed on the thermistor.

This code requires the following elements:
* Thermistor
* 4 Digit 7-Segment display
* Shift Register