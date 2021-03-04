#include "NextClueMusic.h"
#include "pitches.h"

void NextClueMusic::playSuccess(){
	tone(11,NOTE_E7,666);
	delay(750);
	tone(11,NOTE_D7,666);
	delay(750);
	tone(11,NOTE_C7,666);
	delay(750);
	tone(11,NOTE_A7,666);
	delay(750);
	tone(11,NOTE_G7,666);
	delay(750);
	tone(11,NOTE_C8,666);
	delay(750);
}

void NextClueMusic::playFailure(){
	tone(11,NOTE_E7,666);
	delay(750);
	tone(11,NOTE_DS7,666);
	delay(750);
	tone(11,NOTE_D7,666);
	delay(750);
	tone(11,NOTE_CS7,666);
	delay(750);
}

void NextClueMusic::playEntryChirp(){
	tone(11,5000,75);
  delay(100);
}

void NextClueMusic::playTimeoutChirp() {
  tone(11,NOTE_C4,1400);
  delay(1500);
}
