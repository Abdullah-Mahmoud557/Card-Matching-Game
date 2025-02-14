// Deck.h
#ifndef UNTITLED_DECK_H
#define UNTITLED_DECK_H
#include <iostream>
#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"
using namespace std;

class Deck {
private:
    Card** cards;
    bool isPassed;
public:
    Deck();
    Deck(Card** cards);
    void shuffle();
    void displayGrid(const int &x1, const int &y1, const int &x2, const int &y2);
    void setCard(int index, Card* card);
    Card* getCard(int index);
    bool isFinished();
    ~Deck();
};
#endif //UNTITLED_DECK_H
