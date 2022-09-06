#include "Card.h"
#include <cassert>

Card::Card(CardSuit _suit, CardValue _value) : suit(_suit), value(_value) {}

bool Card::isColorCard(bool includeBlack) {
  if (includeBlack && suit == black)
    return true;
  return suit == green || suit == red || suit == blue || suit == yellow;
}

unsigned int Card::getScore(CardSuit tableColor) {
  if (suit == whiteflag)
    return 1;

  if (isColorCard(false) && suit != tableColor)
    return 2;

  if (isColorCard(false) && suit == tableColor)
    return 3;

  if (suit == black)
    return 4;

  if (suit == mermaid)
    return 5;

  if (suit == pirate)
    return 6;

  if (suit == king)
    return 7;

  assert("Score can't be determined");
  return 0;
}