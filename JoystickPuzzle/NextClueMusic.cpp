#include <Tone.h>

void playSuccess(){
	tone.begin(1);
	tone(330,666);
	tone(294,666);
	tone(262,666);
	tone(440,666);
	tone(392,666);
	tone(523,666);
}

void playFailure(){
	tone.begin(1);
	tone(330,666);
	tone(311,666);
	tone(294,666);
	tone(277,666);

}

void playEntryChirp{
	tone.begin(1);
	tone(3000,500);
}