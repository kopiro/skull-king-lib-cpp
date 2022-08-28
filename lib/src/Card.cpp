#include "Card.h"

Card::Card(CardSuit _suit, CardValue _value) : suit(_suit), value(_value) {}

unsigned short Card::getScore() { return 1; }

bool Card::operator<(Card &other) {
  return this->getScore() < other.getScore();
};