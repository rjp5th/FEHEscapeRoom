#include "NextClueMusic.h"

void NextClueMusic::playSuccess(){
	tone(11,330,666);
	delay(666);
	tone(11,294,666);
	delay(666);
	tone(11,262,666);
	delay(666);
	tone(11,440,666);
	delay(666);
	tone(11,392,666);
	delay(666);
	tone(11,523,666);
	delay(666);
}

void NextClueMusic::playFailure(){
	tone(11,330,666);
	delay(666);
	tone(11,311,666);
	delay(666);
	tone(11,294,666);
	delay(666);
	tone(11,277,666);
	delay(666);
}

void NextClueMusic::playEntryChirp(){
	tone(11,3000,500);
}