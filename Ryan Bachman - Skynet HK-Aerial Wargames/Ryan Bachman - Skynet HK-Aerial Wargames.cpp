// Ryan Bachman
// Skynet HK-Aerial V1 assignment.
// October 14, 2018
// CSC215 C/C++ Programming

#include "pch.h"
// Preprocessor directive for console input and output.
#include <iostream>
// Preprocessor directive for using the "random number generator".
#include <cstdlib>
//Preprocessor directive for time to pass the unsigned date and time for seeding the random number.
#include <ctime>

// Global declaration so that I don't have to keep typing std:: for every cout.
using namespace std;

int main() 
{
	// Initialize playAgain char for replayability.
	char playAgain = 'y';

	// Entire program in a while loop in case the player wants to play again.
	while (playAgain == 'y')
	{
		// Most of the variables called inside of the loop so that they don't carry over between loops.

		// Seed random number generator. Uses nullptr instead of 0 since it's a constant.
		srand(static_cast<unsigned int>(time(nullptr)));

		// Random number between 1 and 64 (for 8x8 grid). Constant because it never changes unless recalled.
		const int enemyLocation = rand() % 64 + 1;
		// Keeps track of how many times the UAV pings its radar. Starts at 1 since we don't want ping 0.
		int pings = 1;
		// Sets the low number to 1, so that the prediction can be run in between this and the high number.
		int searchGridLowNumber = 1;
		// Sets the low number to 64, so that the prediction can be run in between this and the low number.
		int searchGridHighNumber = 64;
		// Initializes the location prediction integer as 0, so it exists at the start of the program.
		int targetLocationPrediction = 0;
		// Initializes the Linear AI's prediction number as an int.
		int linearAIPrediction = 0;
		// Initializes the Random AI's prediction number as an int.
		int randomAIPrediction = 0;
		// Initializes the amount of guesses the random AI has made.
		int randomAIGuesses = 1;
		// Initializes the human's prediction number as an int.
		int humanPrediction = 0;
		// Initializes the amount of guesses the human player has made.
		int humanGuesses = 1;

		cout << "\n\nGenerating random enemy location on 8x8 grid....\n";
		cout << "Skynet HK-Aerial Initializing Software.....\n";
		cout << "===========================================================================================\n";

		// While loop, that allows a human player to guess .
		while (humanPrediction != enemyLocation)
		{
			cout << "Please enter a number between 1 and 64: ";
			cin >> humanPrediction;

			// If statement saying that if the prediction is lower than the actual location, it lets you know that your guess was low.
			if (humanPrediction < enemyLocation && humanPrediction >= 1)
			{
				cout << "Your number is too low!\n\n";
				humanGuesses++;
			}
			// Else if statement saying that if the prediction is higher than the actual location, it lets you know that your guess was high.
			else if (humanPrediction > enemyLocation && humanPrediction <= 64)
			{
				cout << "Your number is too high!\n\n";
				humanGuesses++;
			}
			// Else if statement saying that you're doing it wrong if you type something that isn't between 1 and 64.
			else if (humanPrediction > 64 || humanPrediction < 0)
			{
				cout << "You aren't playing this game correctly...\n\n";
			}
			// Else statement saying that if the prediction is correct, it will end the loop. GAME BREAKING IF USER ENTERS ANY LETTERS.
			else
			{
				cout << "You are correct!\n\n";
			}
		}

		// While loop, that runs as long as the UAV prediction is not equal to the enemy's current location.
		while (targetLocationPrediction != enemyLocation)
		{
			// At the start of the loop, it sets the location prediction to the number in the middle of the low number and high number using arithmetic.
			targetLocationPrediction = ((searchGridHighNumber - searchGridLowNumber) / 2) + searchGridLowNumber;

			// If statement saying that if the prediction is lower than the actual location, it sets the new low number to shrink the search area.
			if (targetLocationPrediction < enemyLocation)
			{
				searchGridLowNumber = targetLocationPrediction;
				// Adds one to ping to keep track of how many attempts it took to find the enemy.
				++pings;
			}
			// Else if statement saying that if the prediction is higher than the actual location, it sets the new high number to shrink the search area.
			else if (targetLocationPrediction > enemyLocation)
			{
				searchGridHighNumber = targetLocationPrediction;
				// Adds one to ping to keep track of how many attempts it took to find the enemy.
				++pings;
			}
		}

		// While loop that just adds one to the Linear AI's prediction since it starts at 1 and counts up until it finds the correct location.
		while (linearAIPrediction != enemyLocation)
		{
			// Adds one to linear AI prediction to keep track of how many attempts it took to find the enemy.
			++linearAIPrediction;
		}

		// While loop that goes for as long as randomAIPrediction is not equal to the enemy location.
		while (randomAIPrediction != enemyLocation)
		{
			// Continuously set a new random number whenever the loop goes through.
			randomAIPrediction = rand() % 64 + 1;
			// Adds 1 to guesses ot it can be tracked at the end.
			randomAIGuesses++;
		}

		cout << "========================================================================================================================\n";
		cout << "The player and drones have found the enemy.\n";
		cout << "Enemy was hiding at location #" << enemyLocation << ".\n\n";
		// This cout needed to be noted because for some reason pings is one higher than the actual attempts, so I had to subtract 1 until I figure out why.
		cout << "Skynet HK-Aerial Software took " << pings << " predictions to find the enemy location.\n";
		cout << "The player took " << humanGuesses << " predictions to find the enemy location.\n";
		cout << "The linear AI took " << linearAIPrediction << " predictions to find the enemy location.\n";
		cout << "The random AI took " << randomAIGuesses << " predictions to find the enemy location.\n";
		cout << "========================================================================================================================\n\n";
		cout << "Would you like to play again? (y/n): ";
		cin >> playAgain;
	}

    // Returns 0 to end the program if playAgain does not equal y.
    return 0;
}