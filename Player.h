// Player.h
#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H
#include <iostream>
using namespace std;
class Player {
private:
    string name; // Pointer to dynamically allocated memory
    int score; // Pointer to dynamically allocated memory
    int turns;
public:
    Player();
    Player(string name, int score);
    void displayScore();
    void displayName();
    void setName(string name);
    string getName()  ;
    void setScore(int score);
    int getScore();
    void setTurn(int turns);
    int getTurn();

    virtual ~Player();
};
#endif //UNTITLED_PLAYER_H
