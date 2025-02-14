#include <iostream>
#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
using namespace std;

///Card class
Card::Card() : faceUp(false) {}
Card::Card(bool faceUp) : faceUp(faceUp) {}
void Card::display() { if (faceUp) { cout << "Card"; } else { cout << "*"; } }
void Card::setFaceUp(bool b) { faceUp = b; }
bool Card::getFaceUp() { return faceUp; }
Card::~Card() = default;
//int Card::getDigit(){}
///StandardCard class
StandardCard::StandardCard() :digit(0) {}
StandardCard::StandardCard(bool faceUp, int digit) : Card(faceUp), digit(digit) {}
void StandardCard::display() { if (getFaceUp()) { cout << digit; } else { cout << "*"; } }
void StandardCard::setDigit(int digit) { this->digit = digit; }
int StandardCard::getDigit() { return digit; }
StandardCard::~StandardCard() = default;

///BonusCard class
BonusCard::BonusCard() : digit(7) {}
BonusCard::BonusCard(bool faceUp) : Card(faceUp), digit (7) {}
void BonusCard::display() { if (getFaceUp()) { cout << digit; } else { cout << "*"; } }
BonusCard::~BonusCard() = default;
int BonusCard::getDigit() { return 7; }
///PenaltyCard class
PenaltyCard::PenaltyCard() : digit(8) {}
PenaltyCard::PenaltyCard(bool faceUp) : Card(faceUp), digit (8) {}
void PenaltyCard::display() {if (getFaceUp()) {cout << digit;} else {cout << "*";}}
PenaltyCard::~PenaltyCard() = default;
int PenaltyCard::getDigit() { return 8; }

///Deck class
Deck::Deck() {
    this->isPassed = false;
    cards = new Card*[16];
    for (int i = 0; i < 16; i++) {
        if (i < 12) {
            cards[i] = new StandardCard(false, i % 6 + 1);
        } else if (i < 14) {
            cards[i] = new BonusCard(false);
        } else {
            cards[i] = new PenaltyCard(false);
        }
    }
}

Deck::Deck(Card** cards) {
    this->isPassed = true;
    this->cards = cards;
}

void Deck::shuffle() {
    int shuffled[16];
    for (int i = 0; i < 16; i++) {
        shuffled[i] = -1;
    }
    for (int i = 0; i < 16; i++) {
        int index = std::rand() % 16;
        while (shuffled[index] != -1) {
            index = rand() % 16;
        }
        shuffled[index] = i;
    }
    Card* temp[16];
    for (int i = 0; i < 16; i++) {
        temp[i] = cards[shuffled[i]];
    }
    for (int i = 0; i < 16; i++) {
        cards[i] = temp[i];
    }
}

void Deck::setCard(int index, Card* card) {
    cards[index] = card;
}

Card* Deck::getCard(int index) {
    return cards[index];
}
bool Deck::isFinished(){
    int count=0;
    for(int i=0;i<16;i++){
        if(!this->getCard(i)->getFaceUp())
            count++;
    }
    return count <=1 ;
}

void Deck::displayGrid(const int &x1, const int &y1, const int &x2, const int &y2) {
    cout << "===================" << endl;
    for (int i = 0; i < 16; i++) {
        if (i % 4 == 0) {
            cout << "| ";
        }
        //if the card is flipped up and not of the selected cards display X
        if (cards[i]->getFaceUp() && !(i / 4 == x1 && i % 4 == y1) && !(i / 4 == x2 && i % 4 == y2)) {
            cout << "X";
        } else {
            cards[i]->display();
        }
        cout << " | ";
        if (i % 4 == 3) {
            cout << endl << "===================" << endl;
        }
    }
    cout << endl;
}

Deck::~Deck() {
    if(!isPassed) {
        for (int i = 0; i < 16; i++) {
            delete cards[i];
        }
        delete[] cards;
    }
}

///Player class
Player::Player() : name(""), score(0) {}
Player::Player(string name, int score) : name(name), score(score) {}
void Player::displayScore() {cout << score << endl;}
void Player::displayName() {cout << name << endl;}
void Player::setName(string name) {this->name = name;}
string Player::  getName() {return name;}
void Player::setScore(int score) {this->score = score;}
int Player::getScore() {return score;}
Player::~Player() = default;
int Player::getTurn() {return turns;}
void Player::setTurn(int turn){
this->turns=turn;
}
///Game class
Game::Game(){
    this->isPassed=false;
    turns=0;
    deck=new Deck();
    p1=new Player();
    p2=new Player();
    isPlayerOneTurn = true;
    skipNextTurn = false;
    penaltyPlayer = false;
}
Game::Game(Deck *deck, Player *p1, Player *p2,int turns) {
    this->isPassed = true;
    this->turns = turns;
    this->deck = deck;
    this->p1 = p1;
    this->p2 = p2;
}


void Game::initializeGame() {
    /*Explanation of the initializeGame Method
Game Banner: The method begins by displaying a welcome message to introduce the game.

Random Seed: Initializes the random number generator to ensure shuffling is random each time the game is played.

Player Names: Prompts the user to input names for both Player 1 and Player 2 and sets these names using setName().

Shuffle Deck: The shuffle() method randomizes the positions of the cards in the deck.

Reveal Cards: A loop flips all cards face-up temporarily to display the grid before gameplay begins.

Display Grid: The current state of the card grid is displayed using deck->displayGrid().

Hide Cards: Another loop flips all the cards back face-down to prepare for the game.

Start Game Loop: The gameLoop() method is called to begin the main game logic, where players take turns flipping cards and trying to match them.

This documentation provides clarity for anyone reading the code, explaining the purpose of each step in the initializeGame method.*/
    // Display the game banner
    cout << "=====================================" << endl;
    cout << "       Welcome to the Card Game!     " << endl;
    cout << "=====================================" << endl;

    // Seed the random number generator for shuffling the deck
    srand(static_cast<unsigned>(time(nullptr)));

    // Prompt for Player 1's name
    string name1, name2;
    cout << "Enter name for Player 1: ";
    cin >> name1;
    p1->setName(name1);

    // Prompt for Player 2's name
    cout << "Enter name for Player 2: ";
    cin >> name2;
    p2->setName(name2);

    // Shuffle the deck to randomize card positions
    deck->shuffle();

/*
    // Flip all cards face-up to show the initial deck layout
    for (int i = 0; i < 16; i++) {
        deck->getCard(i)->setFaceUp(true);
    }
*/

    // Display the initial card grid after flipping all cards face-up
    deck->displayGrid(-1,-1,-1,-1);

    // Flip all cards face-down to start the game with hidden cards
    for (int i = 0; i < 16; i++) {
        deck->getCard(i)->setFaceUp(false);
    }

    // Start the main game loop
    gameLoop();
}


void Game::gameLoop() {
    // Main game loop continues until the deck indicates the game is finished
    while (!deck->isFinished()) {
        // Handle skipping a turn if a penalty was previously applied
        if (skipNextTurn && penaltyPlayer == isPlayerOneTurn) {
            cout << "Player: " << (isPlayerOneTurn ? p1->getName() : p2->getName()) << " skipped the turn" << endl;
            skipNextTurn = false;  // Reset the skip flag
            isPlayerOneTurn = !isPlayerOneTurn;  // Switch to the other player's turn
        }

        // Determine the current player (Player 1 or Player 2)
        Player &curr = isPlayerOneTurn ? *p1 : *p2;

        // Execute the current player's turn
        playerTurn(curr);

        // Display the current scores after the turn
        displayScores();
    }

    // Display the winner once the game loop ends
    displayWinner();
}


void Game::playerTurn(Player& curr) {
    int p1x=-1, p1y=-1, p2x=-1, p2y=-1;

    // First card selection by the current player
    selectPosition(curr, p1x, p1y);
    deck->getCard(p1x * 4 + p1y)->setFaceUp(true);
    deck->displayGrid(p1x, p1y, -1, -1);

    // Second card selection by the current player
    selectPosition(curr, p2x, p2y);
    deck->getCard(p2x * 4 + p2y)->setFaceUp(true);
    deck->displayGrid(p1x, p1y, p2x, p2y);

    // Handle the logic for matching or non-matching cards
    handleCardMatch(curr, p1x, p1y, p2x, p2y);

    // Update the number of turns and switch to the next player
    updateTurns();
}


void Game::selectPosition(Player& curr, int& x, int& y) {
    while (true) {
        // Prompt the current player to enter coordinates for a card to flip
        cout << curr.getName() << ", enter the coordinates (x y) of the card to flip: ";
        cin >> x >> y;

        // Validate the input coordinates and check if the card is not already face-up
        if (!(x >= 0 && x < 4 && y >= 0 && y < 4)) {
            cout << "Invalid coordinates. Try again." << endl;
        }
            // Check if the card is already face-up
        else if (deck->getCard(x * 4 + y)->getFaceUp()) {
            cout << "Card is already face-up. Try again." << endl;
        }
            // If the coordinates are valid and the card is face-down, break the loop
        else {
            break;
        }
    }
}


void Game::handleCardMatch(Player& curr, int p1x, int p1y, int p2x, int p2y) {
    // Retrieve the two selected cards
    Card* card1 = deck->getCard(p1x * 4 + p1y);
    Card* card2 = deck->getCard(p2x * 4 + p2y);

    // Check if the digits on the two cards match
    if (card1->getDigit() == card2->getDigit()) {
        // Handle bonus card match
        if (card1->getDigit() == 7) {
            handleBonusCard(curr);
        }
            // Handle penalty card match
        else if (card1->getDigit() == 8) {
            handlePenaltyCard(curr);
        }
            // Handle standard card match
        else {
            curr.setScore(curr.getScore() + 1);
            isPlayerOneTurn = !isPlayerOneTurn;
        }
    } else {
        // Handle non-matching cards
        handleNonMatchingCards(curr, p1x, p1y, p2x, p2y);
    }
}


void Game::handleBonusCard(Player& curr) {
    int r;

    // Prompt the player to choose a reward for matching a bonus card
    cout << "Select Rewards" << endl << "1: +2 points" << endl << "2: gain +1 point and take another turn" << endl;
    cin >> r;

    // Validate the choice
    while (r != 1 && r != 2) {
        cout << "Invalid choice. Try again: ";
        cin >> r;
    }

    // Apply the selected reward
    if (r == 1) {
        curr.setScore(curr.getScore() + 2);
    } else {
        curr.setScore(curr.getScore() + 1);
        isPlayerOneTurn = !isPlayerOneTurn;
    }
}


void Game::handlePenaltyCard(Player& curr) {
    int r;

    // Prompt the player to choose a penalty for matching a penalty card
    cout << "Select Penalty" << endl << "1: Lose 2 points" << endl << "2: lose 1 point and skip the next turn" << endl;
    cin >> r;

    // Validate the choice
    while (r != 1 && r != 2) {
        cout << "Invalid choice. Try again: ";
        cin >> r;
    }

    // Apply the selected penalty
    if (r == 1) {
        curr.setScore(curr.getScore() - 2);
    } else {
        curr.setScore(curr.getScore() - 1);
        skipNextTurn = true;
        penaltyPlayer = isPlayerOneTurn;
    }
}


void Game::handleNonMatchingCards(Player& curr, int p1x, int p1y, int p2x, int p2y) {
    // Get the digits on the selected cards
    int digit1 = deck->getCard(p1x * 4 + p1y)->getDigit();
    int digit2 = deck->getCard(p2x * 4 + p2y)->getDigit();

    // Apply points for bonus or penalty cards if applicable
    if (digit1 == 7 || digit2 == 7) {
        curr.setScore(curr.getScore() + 1);
    }
    if (digit1 == 8 || digit2 == 8) {
        curr.setScore(curr.getScore() - 1);
    }

    // Flip the cards back face-down if they are standard cards (not bonus or penalty)
    if (digit1 < 7) {
        deck->getCard(p1x * 4 + p1y)->setFaceUp(false);
    }
    if (digit2 < 7) {
        deck->getCard(p2x * 4 + p2y)->setFaceUp(false);
    }
}


void Game::updateTurns() {
    //display the grid
    deck->displayGrid(-1,-1,-1,-1);
    // Switch to the other player's turn and increment the turn counter
    isPlayerOneTurn = !isPlayerOneTurn;
    turns++;
}


void Game::displayScores() {
    cout << "===================" << endl;
    cout << "Turns: " << turns << endl;

    // Display Player 1's score
    cout << p1->getName() << "'s score: ";
    p1->displayScore();

    // Display Player 2's score
    cout << p2->getName() << "'s score: ";
    p2->displayScore();

    cout << "===================" << endl;
}

void Game::displayWinner() {
    cout << "===================" << endl;

    // Determine and display the winner based on scores
    if (p1->getScore() == p2->getScore()) {
        cout << "The game is a tie!" << endl;
    } else if (p1->getScore() > p2->getScore()) {
        cout << p1->getName() << " wins!" << endl;
    } else {
        cout << p2->getName() << " wins!" << endl;
    }

    cout << "===================" << endl;
}

Deck* Game::getDeck() { return deck; }
void Game::setDeck(Deck *deck) { this->deck = deck; }
Game::~Game() {
    if(!isPassed){
    delete p1;
    delete p2;
    delete deck;
    }
}

///Main function
int main() {

    Game *game=new Game();
    game->initializeGame();
    delete game;

    return 0;
}
