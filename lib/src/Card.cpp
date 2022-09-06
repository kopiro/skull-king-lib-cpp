#include "Card.h"
#include <cassert>
#include <cmath>
#include <stdexcept>

Card::Card(const CardSuit _suit, const CardValue _value) {
  assert(black - yellow - suitModulo > suitModulo);
  if ((_suit == green || _suit == yellow || _suit == red || _suit == blue ||
       _suit == black) &&
      (_value <= 0)) {
    throw std::invalid_argument("Invalid color card without a positive value");
  } else if ((_suit == pirate || _suit == king || _suit == mermaid ||
              _suit == whiteflag) &&
             _value != SPECIAL) {
    throw std::invalid_argument("Invalid special card without a SPECIAL value");
  } else if (_suit == UNKNOWN && _value != PIRATE_OR_WHITE_FLAG) {
    throw std::invalid_argument(
        "Invalid Unknown card without a PIRATE_OR_WHITE_FLAG value");
  }

  suit = _suit;
  value = _value;
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