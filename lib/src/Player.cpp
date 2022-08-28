#include "Player.h"

Player::Player() {}

void Player::addCardToHand(Card *card) { hand.push_back(card); }
void Player::resetHand() { hand.clear(); }