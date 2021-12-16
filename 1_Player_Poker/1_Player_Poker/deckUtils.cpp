#include "deckUtils.h"
#include <random>
#include <time.h>

void cardDeck::createDeck() {
	m_deck.resize(52);

	singleCard* pushed_card = new singleCard;

	int suitCounter = 0;
	int valueCounter = 0;
	int totalCounter = 0;

	while(suitCounter <= 3) {
		while(valueCounter <= 12) {
			convertFromIntToEnum(*pushed_card, valueCounter, suitCounter);
			//std::cout << "suitCounter: " << suitCounter << std::endl;
			//std::cout << "valueCounter: " << valueCounter << std::endl;
			//std::cout << "size(): " << m_deck.size() << std::endl;
			m_deck.at(totalCounter) = *pushed_card;

			valueCounter++;
			totalCounter++;
		}
		valueCounter = 0;

		suitCounter++;
	}
	return;
}

void cardDeck::convertFromIntToEnum(singleCard& card_1, int value, int suit) {

	cardDef::valueType returnVal = cardDef::valueType::Ace;
	cardDef::suitType returnSuit = cardDef::suitType::Spades;

	switch (value) {
	case 0:
		returnVal = cardDef::valueEnum::Ace;
		break;
	case 1:
		returnVal = cardDef::valueEnum::One;
		break;
	case 2:
		returnVal = cardDef::valueEnum::Two;
		break;
	case 3:
		returnVal = cardDef::valueEnum::Three;
		break;
	case 4:
		returnVal = cardDef::valueEnum::Four;
		break;
	case 5:
		returnVal = cardDef::valueEnum::Five;
		break;
	case 6:
		returnVal = cardDef::valueEnum::Six;
		break;
	case 7:
		returnVal = cardDef::valueEnum::Seven;
		break;
	case 8:
		returnVal = cardDef::valueEnum::Eight;
		break;
	case 9:
		returnVal = cardDef::valueEnum::Nine;
		break;
	case 10:
		returnVal = cardDef::valueEnum::Ten;
		break;
	case 11:
		returnVal = cardDef::valueEnum::Jack;
		break;
	case 12:
		returnVal = cardDef::valueEnum::Queen;
		break;
	case 13:
		returnVal = cardDef::valueEnum::King;
		break;
	}

	switch (suit) {
	case 0:
		returnSuit = cardDef::suitEnum::Spades;
		break;
	case 1:
		returnSuit = cardDef::suitEnum::Clubs;
		break;
	case 2:
		returnSuit = cardDef::suitEnum::Hearts;
		break;
	case 3:
		returnSuit = cardDef::suitEnum::Diamonds;
		break;
	}

	singleCard returnCard;

	returnCard.m_value = returnVal;
	returnCard.m_suit = returnSuit;

	card_1 = returnCard;

	return;
}

void cardDeck::shuffleDeck() {
	time_t timer;
	unsigned int seed = (unsigned int)time(&timer);
	srand(seed);

	int randomNumber = 0;
	singleCard* tempCard = new singleCard;

	std::cout << "Shuffling!" << std::endl;

	for (int iteratorCounter = 0; iteratorCounter <= m_numOfShuffleIterations; iteratorCounter++) {
		randomNumber = rand() % 52;
		
		*tempCard = m_deck.at(randomNumber);

		m_deck.erase(m_deck.begin() + randomNumber);

		m_deck.push_back(*tempCard);
	}

	//~tempCard();

	std::cout << "Shuffled!" << std::endl;
	return;
}

bool cardDeck::isDeckEmpty() {
	if (m_deck.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

void cardDeck::discardDeck() {
	m_deck.clear();

	return;
}

void cardDeck::printDeck() {
	std::string spades = "Spades";
	std::string clubs = "Clubs";
	std::string hearts = "Hearts";
	std::string diamonds = "Diamonds";

	std::cout << "#############################################" << std::endl;

	for (int i = 0; i != m_deck.size(); i++) {
		switch (m_deck.at(i).m_suit) {
		case 0:
			std::cout << m_deck.at(i).m_value << " of " << spades << std::endl;
			break;
		case 1:
			std::cout << m_deck.at(i).m_value << " of " << clubs << std::endl;
			break;
		case 2:
			std::cout << m_deck.at(i).m_value << " of " << hearts << std::endl;
			break;
		case 3:
			std::cout << m_deck.at(i).m_value << " of " << diamonds << std::endl;
			break;
		}
	}

	std::cout << "#############################################" << std::endl;

	return;
}

//######################################################################
//#                                                                    #
//#                   CARD HAND HELPER FUNCTIONS                       #
//#                                                                    #
//######################################################################

void cardHand::drawFiveCards(cardDeck* Deck, cardHand* Hand) {

	singleCard* tempCard = new singleCard;

	for (int i = 0; i <= 4; i++) {
		if (Deck->isDeckEmpty()) {
			std::cout << "ERROR!, DECK EMPTY" << std::endl;
			break;
		}
		else {
			*tempCard = Deck->m_deck.back();
			Deck->m_deck.pop_back();
			Hand->m_hand.push_back(*tempCard);
		}
	}

	return;
}

void cardHand::replaceCards(cardDeck* Deck, cardHand* Hand, std::vector<std::string> positionVector) {

	std::string One = "1";
	std::string Two = "2";
	std::string Three = "3";
	std::string Four = "4";
	std::string Five = "5";

	int position = 0;

	std::sort(positionVector.begin(), positionVector.end());

	for (int i = positionVector.size() - 1; i != -1; i--) { // Remove cards from Hand
		if (positionVector.at(i) == One) {
			position = 1;
		}
		else if (positionVector.at(i) == Two) {
			position = 2;
		}
		else if (positionVector.at(i) == Three) {
			position = 3;
		}
		else if (positionVector.at(i) == Four) {
			position = 4;
		}
		else if (positionVector.at(i) == Five) {
			position = 5;
		}
		Hand->m_hand.erase(Hand->m_hand.begin() + position - 1);
	}
	
	Hand->m_hand.shrink_to_fit(); // Shrink Hand so when cards are added back, it wont go beyond 5 cards

	singleCard* tempCard = new singleCard;

	for (int i = 0; i != positionVector.size(); i++) {
		if (Deck->isDeckEmpty()) {
			std::cout << "ERROR!, DECK EMPTY" << std::endl;
		}
		else {
			*tempCard = Deck->m_deck.back();
			Deck->m_deck.pop_back();
			Hand->m_hand.push_back(*tempCard);

		}
	}

	return;
}

void cardHand::discardCards(cardHand* Hand) {
	Hand->m_hand.clear();

	return;
}

void cardHand::printHand(cardHand* Hand) {

	std::cout << "################ HAND Begin ################" << std::endl;

	std::string spades = "Spades";
	std::string clubs = "Clubs";
	std::string hearts = "Hearts";
	std::string diamonds = "Diamonds";

	for (int i = 0; i != Hand->m_hand.size(); i++) {
		switch (Hand->m_hand.at(i).m_suit) {
		case 0:
			std::cout << Hand->m_hand.at(i).m_value << " of " << spades << std::endl;
			break;
		case 1:
			std::cout << Hand->m_hand.at(i).m_value << " of " << clubs << std::endl;
			break;
		case 2:
			std::cout << Hand->m_hand.at(i).m_value << " of " << hearts << std::endl;
			break;
		case 3:
			std::cout << Hand->m_hand.at(i).m_value << " of " << diamonds << std::endl;
			break;
		}
	}

	std::cout << "################# HAND End #################" << std::endl;

	return;
}

int cardHand::determineHandValue(int betValue, cardHand* Hand) {
	int returnValue = -1 * betValue;

	//Need to sort hand first ... Need to write my own sort for this class specifically
	//std::sort(Hand->m_hand.begin(), Hand->m_hand.end());
	cardHand::sortHand(Hand);

	//determine royal flush (King Queen Jack 10 Ace matching suits)
	if (Hand->m_hand.at(0).m_suit == Hand->m_hand.at(1).m_suit && Hand->m_hand.at(1).m_suit == Hand->m_hand.at(2).m_suit
		&& Hand->m_hand.at(2).m_suit == Hand->m_hand.at(3).m_suit && Hand->m_hand.at(3).m_suit == Hand->m_hand.at(4).m_suit)
	{
		if (isThereACardValue(Hand->Ace, Hand) && isThereACardValue(Hand->Ten, Hand) && isThereACardValue(Hand->Jack, Hand)
			&& isThereACardValue(Hand->Queen, Hand) && isThereACardValue(Hand->King, Hand))
		{
			for (auto& item : Hand->winningHandsMap) { //This is for readabillity. I would fix this later.
				if (item.first == RoyalFlush) {
					return item.second * betValue;
				}
			}
		}
	}

	// Determine four of a kind (and 4 cards that match value)
	bool FourOfAKindFound = false;
	int matchCount = 0;
	for (int i = 0; i <= 1; i++) {
		for (int j = i; j <= 4; j++) {
			if (Hand->m_hand.at(i).m_value == Hand->m_hand.at(j).m_value) {
				matchCount++;
			}
			if (matchCount == 4) {
				FourOfAKindFound = true;
			}
		}
		matchCount = 0;
	}
	if (FourOfAKindFound == true) {
		for (auto& item : Hand->winningHandsMap) {
			if (item.first == FourOfAKind) {
				return item.second * betValue;
			}
		}
	}
	

	// Determine Full House
	int cardValueCount[14];
	for (int i = 0; i <= 13; i++) {
		for (int j = 0; j <= 4; j++) {
			if (Hand->m_hand.at(j).m_value == i) {
				cardValueCount[i]++;
			}
		}
	}

	int cardValueMaxA = 0; //This is the highest count of matching cards of value
	int cardValueMaxB = 0; //This is the second highest count of matching cards of value
	for (int i = 0; i <= 13; i++) {
		if (cardValueMaxA <= cardValueCount[i]) {
			cardValueMaxA = cardValueCount[i];
		}
	}
	for (int i = 0; i <= 13; i++) {
		if (cardValueMaxB <= cardValueCount[i] && cardValueMaxB < cardValueMaxA) {
			cardValueMaxB = cardValueCount[i];
		}
	}
	if (cardValueMaxA == 3 && cardValueMaxB == 2 || cardValueMaxA == 2 && cardValueMaxB == 3) {
		for (auto& item : Hand->winningHandsMap) {
			if (item.first == FullHouse) {
				return item.second * betValue;
			}
		}
	}

	
	//Determine straight
	if (Hand->m_hand.at(0).m_value == Hand->m_hand.at(1).m_value - 1) {
		if (Hand->m_hand.at(1).m_value == Hand->m_hand.at(2).m_value - 1) {
			if (Hand->m_hand.at(2).m_value == Hand->m_hand.at(3).m_value - 1) {
				if (Hand->m_hand.at(3).m_value == Hand->m_hand.at(4).m_value - 1) {
					for (auto& item : Hand->winningHandsMap) {
						if (item.first == FullHouse) {
							return item.second * betValue;
						}
					}
				}
			}
		}
	}


	//Determine 3 of a kind

	//Determine 2 of a kind

	return returnValue;
}

bool cardHand::isThereACardValue(cardDef::valueType Value, cardHand* Hand) {
	bool returnBool = false;

	for (int i = 0; i <= 4; i++) {
		if (Hand->m_hand.at(i).m_value == Value) {
			returnBool = true;
			break;
		}
	}

	return returnBool;
}

bool cardHand::isThereACardSuit(cardDef::suitType Suit, cardHand* Hand) {
	bool returnBool = false;

	for (int i = 0; i <= 4; i++) {
		if (Hand->m_hand.at(i).m_suit == Suit) {
			returnBool = true;
			break;
		}
	}

	return returnBool;
}

void cardHand::sortHand(cardHand* Hand) {
	std::vector<singleCard> copyHand = {};
	//copyHand.resize(0);

	//copyHand.swap(Hand->m_hand);

	for (auto i : Hand->m_hand)
	{
		copyHand.push_back(i);
	}

	singleCard copyCard1;
	singleCard copyCard2;
	singleCard copyCard3;
	singleCard copyCard4;
	singleCard copyCard5;
	singleCard tempCard1;

	copyCard1 = copyHand.at(0);
	copyCard2 = copyHand.at(1);
	copyCard3 = copyHand.at(2);
	copyCard4 = copyHand.at(3);
	copyCard5 = copyHand.at(4);



	//Sort low to high for both enums for suit and value
	//First by value
	bool rerunSort = true;

	while (rerunSort == true)
	{
		rerunSort = false;

		if ((int)copyCard1.m_value > (int)copyCard2.m_value)
		{
			tempCard1 = copyCard2;
			copyCard2 = copyCard1;
			copyCard1 = tempCard1;

			rerunSort = true;
		}
		if ((int)copyCard2.m_value > (int)copyCard3.m_value)
		{
			tempCard1 = copyCard3;
			copyCard3 = copyCard2;
			copyCard2 = tempCard1;

			rerunSort = true;
		}
		if ((int)copyCard3.m_value > (int)copyCard4.m_value)
		{
			tempCard1 = copyCard4;
			copyCard4 = copyCard3;
			copyCard3 = tempCard1;

			rerunSort = true;
		}
		if ((int)copyCard4.m_value > (int)copyCard5.m_value)
		{
			tempCard1 = copyCard5;
			copyCard5 = copyCard4;
			copyCard4 = tempCard1;

			rerunSort = true;
		}
	}

	copyHand.clear();
	copyHand.resize(0);

	copyHand.push_back(copyCard1);
	copyHand.push_back(copyCard2);
	copyHand.push_back(copyCard3);
	copyHand.push_back(copyCard4);
	copyHand.push_back(copyCard5);

	Hand->m_hand.clear();

	for (auto i : copyHand)
	{
		Hand->m_hand.push_back(i);
	}

	std::cout << "########################### Sorted Hand ###########################" << std::endl;
	std::cout << (int)Hand->m_hand.at(0).m_value << " of " << (int)Hand->m_hand.at(0).m_suit << std::endl;
	std::cout << (int)Hand->m_hand.at(1).m_value << " of " << (int)Hand->m_hand.at(1).m_suit << std::endl;
	std::cout << (int)Hand->m_hand.at(2).m_value << " of " << (int)Hand->m_hand.at(2).m_suit << std::endl;
	std::cout << (int)Hand->m_hand.at(3).m_value << " of " << (int)Hand->m_hand.at(3).m_suit << std::endl;
	std::cout << (int)Hand->m_hand.at(4).m_value << " of " << (int)Hand->m_hand.at(4).m_suit << std::endl;
	std::cout << "########################### Sorted Hand ###########################" << std::endl;

	return;

	//Then by suit
	/*
	rerunSort = true;

	while (rerunSort == true)
	{
		rerunSort = false;

		if ((int)copyCard1.m_suit > (int)copyCard2.m_suit)
		{
			tempCard1 = copyCard2;
			copyCard2 = copyCard1;
			copyCard1 = tempCard1;

			rerunSort = true;
		}
		if ((int)copyCard2.m_suit > (int)copyCard3.m_suit)
		{
			tempCard1 = copyCard3;
			copyCard3 = copyCard2;
			copyCard2 = tempCard1;

			rerunSort = true;
		}
		if ((int)copyCard3.m_suit > (int)copyCard4.m_suit)
		{
			tempCard1 = copyCard4;
			copyCard4 = copyCard3;
			copyCard3 = tempCard1;

			rerunSort = true;
		}
		if ((int)copyCard4.m_suit > (int)copyCard5.m_suit)
		{
			tempCard1 = copyCard5;
			copyCard5 = copyCard4;
			copyCard4 = tempCard1;

			rerunSort = true;
		}
	}
	

	std::cout << (int)copyCard1.m_value << " of " << (int)copyCard1.m_suit << std::endl;
	std::cout << (int)copyCard2.m_value << " of " << (int)copyCard2.m_suit << std::endl;
	std::cout << (int)copyCard3.m_value << " of " << (int)copyCard3.m_suit << std::endl;
	std::cout << (int)copyCard4.m_value << " of " << (int)copyCard4.m_suit << std::endl;
	std::cout << (int)copyCard5.m_value << " of " << (int)copyCard5.m_suit << std::endl;
	*/
	/*
	//clear original hand and place copyHand back in to main Hand so that the Hand can be returned
	Hand->discardCards(Hand);
	singleCard tempCard;
	for (int i = 0; i <= 4; i++)
	{
		tempCard.m_suit = copyHand.at(i)->m_suit;
		tempCard.m_value = copyHand.at(i)->m_value;
		Hand->m_hand.push_back(tempCard);
	}
	*/
}