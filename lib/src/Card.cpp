#include "Card.h"

Card::Card(CardSuit _suit, CardValue _value) : suit(_suit), value(_value) {}

bool Card::isColorCard(bool includeBlack) {
  return suit == green || suit == red || blue == suit || yellow;
}

CardSuit Card::getSuit() { return suit; }
CardValue Card::getValue() { return value; }

unsigned int Card::getScore(CardSuit tableColor) {
  if (suit == whiteflag) {
    return 1;
  }

  if (isColorCard(false) && suit != tableColor) {
    return 2;
  }

  if (isColorCard(false) && suit == tableColor) {
    return 3;
  }

  if (suit == CardSuit::black) {
    return 4;
  }

  if (suit == CardSuit::mermaid) {
    return 5;
  }

  if (suit == CardSuit::pirate) {
    return 6;
  }

  if (suit == CardSuit::king) {
    return 7;
  }
}