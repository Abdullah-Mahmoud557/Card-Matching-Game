// StandardCard.h
#ifndef UNTITLED_STANDARDCARD_H
#define UNTITLED_STANDARDCARD_H
#include <iostream>
#include "Card.h"
using namespace std;
class StandardCard : public Card {
private:
    int digit;
public:
    StandardCard();
    StandardCard(bool faceUp, int digit);
    void display() override;
    void setDigit(int digit);
    int getDigit() override;
    ~StandardCard();
};
#endif //UNTITLED_STANDARDCARD_H
