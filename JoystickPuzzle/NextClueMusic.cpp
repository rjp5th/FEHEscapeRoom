#include "NextClueMusic.h"

void NextClueMusic::playSuccess(){
	tone(11,NOTE_E6,666);
	delay(750);
	tone(11,NOTE_D6,666);
	delay(750);
	tone(11,NOTE_C6,666);
	delay(750);
	tone(11,NOTE_A6,666);
	delay(750);
	tone(11,NOTE_G6,666);
	delay(750);
	tone(11,NOTE_C7,666);
	delay(750);
}

void NextClueMusic::playFailure(){
	tone(11,NOTE_E6,666);
	delay(750);
	tone(11,NOTE_DS6,666);
	delay(750);
	tone(11,NOTE_D6,666);
	delay(750);
	tone(11,NOTE_CS6,666);
	delay(750);
}

void NextClueMusic::playEntryChirp(){
	tone(11,8000,500);
}