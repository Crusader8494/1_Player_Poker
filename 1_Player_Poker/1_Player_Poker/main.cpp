#include <iostream>
#include <stdlib.h>
#include "main.h"
#include "deckUtils.h"

int main() {
	
	cardDeck* Deck_1 = new cardDeck;
	cardHand* Hand_1 = new cardHand;

	int bankValue = 1000;
	int& bankValueRef = bankValue;
	int betValue = 1;
	int& betValueRef = betValue;
	int returnValueOfBet = 0;

	while (1) {
		//clear screen
		system("CLS");

		//retrieve bet
		retrieveBetValue(betValueRef, bankValueRef);

		//setup
		initializePoker(Deck_1); //setup Game, Objects and Variables
		drawHand(Deck_1, Hand_1);
		Hand_1->printHand(Hand_1);

		//discard
		std::vector<std::string> userInputVector = userDiscard(); //retrieve a vector of error checked user inputs
		internalDiscard(userInputVector, Deck_1, Hand_1);
		Hand_1->printHand(Hand_1);

		//determine hand value
		returnValueOfBet = Hand_1->determineHandValue(betValue, Hand_1);

		//add or subtract from bank
		if (returnValueOfBet >= 0) {
			std::cout << "You Won " << returnValueOfBet << std::endl;
			bankValue += returnValueOfBet; // already subtracted in initial bet so we only need this in the win condition
		}
		else {
			std::cout << "You Lost " << (-1 * returnValueOfBet) << std::endl;
		}
		std::cout << "Your Bank currently has: " << bankValue << " coin(s)" << std::endl;

		//cleanup
		userInputVector.clear();
		userInputVector.shrink_to_fit();
		Deck_1->discardDeck();
		Hand_1->discardCards(Hand_1);

		//pause
		if (bankValue <= 0) {
			system("CLS");
			std::cout << "YOU LOSE!" << std::endl;
			return 0;
		}
		system("PAUSE");
	}
	return 0;
}

void initializePoker(cardDeck *Deck) {
	Deck->createDeck();
	Deck->shuffleDeck();

	//Deck->printDeck();

	return;
}

void drawHand(cardDeck* Deck, cardHand* Hand) {

	Hand->drawFiveCards(Deck, Hand);

	return;
}

std::vector<std::string> userDiscard() {

	std::string userInput = "";
	std::vector<std::string> userInputVector;

	//discard
	int maxIterations = 5;
	int iterationCounter = 0;

	while (1) {
		std::cout << "Use numbers to indicate which cards to discard, input Q to end" << std::endl << "Discard Cards: ";
		std::cin >> userInput;

		bool alreadyThere = false;
		for (int i = 0; i != userInputVector.size(); i++) {
			if (userInput == userInputVector.at(i)) {
				alreadyThere = true;
			}
		}

		if (alreadyThere == false) {
			if (userInput == "1" || userInput == "2" || userInput == "3" || userInput == "4" || userInput == "5") {
				userInputVector.push_back(userInput);
				iterationCounter++;
			}
			else if (userInput == "Q") {
				std::cout << "Breaking Out Of Loop" << std::endl;
				std::cout << "Discarding " << userInputVector.size() << " card(s)" << std::endl;
				break;
			}
			else {
				std::cout << "ERROR: Not a valid selection. Please use numbers (1-5)" << std::endl;
			}

			if (iterationCounter == maxIterations) {
				std::cout << "ERROR: Maximum input reached!" << std::endl;
				std::cout << "Discarding 5 card(s)" << std::endl;
				break;
			}
		}
		else {
			std::cout << "You have already selected that" << std::endl;
		}
	}

	return userInputVector;
}

void internalDiscard(std::vector<std::string> userInput, cardDeck* Deck, cardHand* Hand) {
	
	Hand->replaceCards(Deck, Hand, userInput); // fix order of arguments later
	
	return;
}

void retrieveBetValue(int& bet, int& bank) {

	std::cout << "Your current bank value is: " << bank << std::endl;

	std::cout << "Place a bet: ";
	std::cin >> bet;
	if (bet < 1) {
		std::cout << "ERROR: Bet must be a positive integer >= 1!" << std::endl;
		retrieveBetValue(bet, bank);
	}
	if (bet > bank) {
		std::cout << "ERROR: You cannot bet more than you have." << std::endl;
		retrieveBetValue(bet, bank);
	}

	bank -= bet;

	std::cout << std::endl;
	return;
}