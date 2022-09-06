#pragma once

enum CardSuit {
  UNKNOWN = 0,
  whiteflag,
  green,
  red,
  blue,
  yellow,
  black,
  mermaid,
  pirate,
  pirateOrWhiteflag,
  king,
};

enum CardValue {
  SPECIAL = 0,
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
  unsigned int getScore(CardSuit tableColor);
};