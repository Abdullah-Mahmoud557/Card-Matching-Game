#ifndef UNTITLED_CARD_H
#define UNTITLED_CARD_H
#include <iostream>
using namespace std;
class Card {
private:
    bool faceUp;

public:
    Card();
    Card(bool faceUp);
    virtual void display();
    virtual int getDigit()=0;
    void setFaceUp(bool b);
    bool getFaceUp();
    virtual ~Card();
};
#endif //UNTITLED_CARD_H
