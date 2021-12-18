#ifndef DECKUTILS_H
#define DECKUTILS_H

#include <iostream>
#include <vector>
#include <map>

class cardDef {
public:
	enum valueEnum { //value
		Ace,
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King
	};

	enum suitEnum { //suit
		Spades,
		Clubs,
		Hearts,
		Diamonds
	};

	enum winningHands {
		Pair,
		ThreeOfAKind,
		Straight,
		Flush,
		FullHouse,
		FourOfAKind,
		StraightFlush,
		RoyalFlush
	};

	std::map<winningHands, int> winningHandsMap {
		{ winningHands::Pair, 1},
		{ winningHands::ThreeOfAKind, 3},
		{ winningHands::Straight, 4},
		{ winningHands::Flush, 6},
		{ winningHands::FullHouse, 9},
		{ winningHands::FourOfAKind, 25},
		{ winningHands::RoyalFlush, 250}
	};

	typedef suitEnum suitType; //renamed enumeration into a type
	typedef valueEnum valueType; //renamed enumeration into a type
	//typedef std::vector<singleCard> deckType; //Deck of Cards, vector of individual card classes

};

class singleCard : cardDef {
public:

	cardDef::valueType m_value = cardDef::valueType::Ace;
	cardDef::suitType m_suit = cardDef::suitType::Spades;

	singleCard() {
		//m_value = cardDef::valueType::Ace;
		//m_suit = cardDef::suitType::Spades;
	}
};

class cardDeck : cardDef {
public:

	std::vector<singleCard> m_deck;

	const int m_numOfShuffleIterations = 32767;

	void createDeck();
	void convertFromIntToEnum(singleCard& card_1, int value, int suit);
	void shuffleDeck();
	bool isDeckEmpty();
	void discardDeck();
	void printDeck(); // used for debug

	cardDeck() {
		//this->createDeck();
	}
};


class cardHand : cardDef {
public:
	std::vector<singleCard> m_hand;

	void drawFiveCards(cardDeck* Deck, cardHand* Hand);
	void replaceCards(cardDeck* Deck, cardHand* Hand, std::vector<std::string> positionVector);
	void discardCards(cardHand* Hand);
	void printHand(cardHand* Hand);
	int determineHandValue(int betValue, cardHand* Hand);
	bool isThereACardValue(cardDef::valueType Value, cardHand* Hand);
	bool isThereACardSuit(cardDef::suitType Suit, cardHand* Hand);
	void sortHand(cardHand* Hand);

	cardHand() {
		m_hand.resize(0);
	}
};

#endif