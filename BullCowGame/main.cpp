/* This is the console executable, that makes use of the BullCow class. 
This acts as the view  in a MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class.*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string; 
using int32 = int; 

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game, which we reuse across play 

// the entry point for the game
int main() {

	bool bPlayAgain = false;
	do {
		
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << "\n";
	} while (bPlayAgain);

	return 0;//exit the application
}


// introduce the game
void PrintIntro() {

	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << "\n";
	return;
}

// plays a single game to completion
void PlayGame() {

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {

		FText Guess = GetValidGuess(); 

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


// loop continually until the user gives a valid guess
FText GetValidGuess() { 
	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}


void PrintGameSummary() {

	int32 MaxTries = BCGame.GetMaxTries();
	if (BCGame.IsGameWon()) {
		
		std::cout << "Wow! Such game! Much winning!\n";
	} else {
		std::cout << "Better luck next time!\n";
	}
	return;
}


bool AskToPlayAgain() {
	
		std::cout << "Do you want to play again with the same hidden word? (y/n) ";
		FText Response = "";
		getline(std::cin, Response);
		std::cout << "\n";
		return ((Response[0] == 'y') || (Response[0] == 'Y'));
} 
