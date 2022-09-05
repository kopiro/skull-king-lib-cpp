#include "Player.h"

Player::Player(std::string _name) : name(_name) {}

void Player::addCardToHand(Card *card) { hand.push_back(card); }
void Player::resetHand() { hand.clear(); }