#pragma once
#include "FBullCowGame.h"
#include <map>
#include <vector>

// TODO make feature that checks that random word wasn't shown before (create a separate map of used words and compare )

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int; 

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const { 
	
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

// TODO create function that randomly selects the word from a map and assigns it to MyHiddenWord 

// TODO create function that will choose which map we choose from depending on the word length choosen by player

// TODO call this function in the game somewhere
void FBullCowGame::ChooseHiddenWord(FString UserLength) {

	
	// Making 5 vectors of words
	std::vector<FString> ThreeLetter = { "ant","bat","cat","cow","dog","elk","fox","owl","pig","rat" };
	std::vector<FString> FourLetter = { "lion", "duck", "wolf", "goat", "bear", "frog", "seal", "crab", "mole", "swan" };
	std::vector<FString> FiveLetter = { "sloth", "tiger", "shark", "squid", "snail", "snake", "whale", "horse", "zebra", "human" };
	std::vector<FString> SixLetter = { "monkey", "donkey", "spider", "lizard", "oyster", "wombat", "dragon", "walrus", "shrimp", "falcon" };
	std::vector<FString> SevenLetter = { "echidna", "warthog", "pelican", "panther", "ostrich", "monster", "lobster", "hamster", "dolphin", "catfish" };
	
	TMap<FString, std::vector<FString>> WordLengthToVectorName{ { "3", ThreeLetter }, {"4", FourLetter}, {"5", FiveLetter}, {"6", SixLetter}, {"7", SevenLetter} };
	
	WordLengthToVectorName[UserLength]; // gets the vector of words depending on the choosen word length
	// TODO test if the proper map outputs


	return;
}

void FBullCowGame::Reset() {

	const FString HIDDEN_WORD = "war"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	
	if (!IsIsogram(Guess)) { // if the guess isn't an isogram, 

		return EGuessStatus::Not_Isogram;

	} else if (!IsLowercase(Guess)) { // if the guess isn't all lowercase 

		return EGuessStatus::Not_Lowercase;

	} else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong

		return EGuessStatus::Wrong_Length;
	
	}
	else { // otherwise

		return EGuessStatus::OK;
	}
}


// receives a valid guess, increments turns and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				//if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; //increment bulls 
				}
				else {
					BullCowCount.Cows++; //increment cows
				}
			}
		}
	}
	
	if (BullCowCount.Bulls == WordLength) {
		
		bGameIsWon = true;
	}
	else { 
		
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) { // for al letters of the word
		
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true; // add the letter to the map
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {

		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
