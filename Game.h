#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H
#include <iostream>
#include "Deck.h"
#include "Player.h"
using namespace std;
class Game {
private:
    Player* p1;
    Player* p2;
    Deck* deck;
    bool isPassed;
    int turns;
    bool isPlayerOneTurn;
    bool skipNextTurn;
    bool penaltyPlayer;
public:
    Game();
    Game(Deck* deck, Player* player1, Player* player2, int turns);
    void initializeGame();
    void gameLoop();
    void playerTurn(Player& curr);
    void selectPosition(Player& curr, int& x, int& y);
    void handleCardMatch(Player& curr, int p1x, int p1y, int p2x, int p2y);
    void handleBonusCard(Player& curr);
    void handlePenaltyCard(Player& curr);
    void handleNonMatchingCards(Player& curr, int p1x, int p1y, int p2x, int p2y);
    void updateTurns();
    void displayScores();
    void displayWinner();
    Deck* getDeck();//Returns the deck
    void setDeck(Deck *deck);//Returns the deck
    virtual ~Game();
};
#endif //UNTITLED_GAME_H