#include "NextClueMusic.h"
#include "pitches.h"

void NextClueMusic::playSuccess(){
	tone(BUZZER_PIN,NOTE_E7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_D7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_C7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_A7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_G7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_C8,666);
	delay(750);
}

void NextClueMusic::playFailure(){
	tone(BUZZER_PIN,NOTE_E7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_DS7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_D7,666);
	delay(750);
	tone(BUZZER_PIN,NOTE_CS7,666);
	delay(750);
}

void NextClueMusic::playEntryChirp(){
	tone(BUZZER_PIN,5000,75);
  delay(100);
}

void NextClueMusic::playTimeoutChirp() {
  tone(BUZZER_PIN,NOTE_C4,1400);
  delay(1500);
}
