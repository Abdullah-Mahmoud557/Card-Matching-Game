// BonusCard.h
#ifndef UNTITLED_BONUSCARD_H
#define UNTITLED_BONUSCARD_H
#include <iostream>
#include "Card.h"
using namespace std;
class BonusCard : public Card {
private:
    int digit;
public:
    BonusCard();
    BonusCard(bool faceUp);
    void display() override;
    int getDigit();
    ~BonusCard();
};
#endif //UNTITLED_BONUSCARD_H
