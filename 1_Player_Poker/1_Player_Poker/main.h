#ifndef MAIN_H
#define MAIN_H
#include "deckUtils.h"

int main();
void initializePoker(cardDeck *Deck);
void drawHand(cardDeck* Deck, cardHand* Hand);
std::vector<std::string> userDiscard();
void internalDiscard(std::vector<std::string> userInput, cardDeck* Deck, cardHand* Hand);
void retrieveBetValue(int& bet, int& bankValueRef);

#endif