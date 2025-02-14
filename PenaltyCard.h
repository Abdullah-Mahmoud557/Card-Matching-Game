// PenaltyCard.h
#ifndef UNTITLED_PENALTYCARD_H
#define UNTITLED_PENALTYCARD_H
#include <iostream>
#include "Card.h"
using namespace std;

class PenaltyCard : public Card {
private:
    int digit; // Pointer to dynamically allocated memory
public:
    PenaltyCard();
    PenaltyCard(bool faceUp);
    void display() override;
    int getDigit();
    ~PenaltyCard();
};
#endif //UNTITLED_PENALTYCARD_H
