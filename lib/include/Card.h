#pragma once

#include <assert.h>

const unsigned short suitModulo = 10;

// The suit represents also the power of the card
// Since colors all are graded the same, we keep a distance of "10"
// between each suit, so that by floor(suit/10) we can still get the proper
// value
enum CardSuit {
  UNKNOWN = -1,
  whiteflag = suitModulo * 1,
  green = (suitModulo * 2 + 1),
  red = (suitModulo * 2) + 2,
  blue = (suitModulo * 2) + 3,
  yellow = (suitModulo * 2) + 4,
  black = suitModulo * 5,
  mermaid = suitModulo * 6,
  pirate = suitModulo * 7,
  king = suitModulo * 8,
};

enum CardValue {
  SPECIAL = -1,
  PIRATE_OR_WHITE_FLAG = -2,
  one = 1,
  two = 2,
  three = 3,
  four = 4,
  five = 5,
  six = 6,
  seven = 7,
  eight = 8,
  nine = 9,
  ten = 10,
  eleven = 11,
  twelve = 12,
  thirteen = 13
};

class Card {
public:
  Card(CardSuit _suit, CardValue _value);
  const CardSuit suit;
  const CardValue value;

  bool isColorCard(bool includeBlack);
  unsigned short getRank(CardSuit tableColor);
};