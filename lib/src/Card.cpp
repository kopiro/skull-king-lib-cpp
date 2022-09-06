#include "Card.h"
#include <cassert>
#include <cmath>

Card::Card(CardSuit _suit, CardValue _value) : suit(_suit), value(_value) {
  assert(black - yellow - suitModulo > suitModulo);
}

bool Card::isColorCard(bool includeBlack) {
  if (includeBlack && suit == black)
    return true;
  return suit == green || suit == red || suit == blue || suit == yellow;
}

unsigned short Card::getRank(CardSuit tableColor) {
  const unsigned short addScore = suit == tableColor ? suitModulo : 0;
  return std::floor((suit + addScore) / suitModulo);
}