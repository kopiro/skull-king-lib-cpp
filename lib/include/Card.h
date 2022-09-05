#pragma once

enum CardSuit {
  UNKNOWN,
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
  special = 0,
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
private:
  CardSuit suit;
  CardValue value;

public:
  Card(CardSuit _suit, CardValue _value);
  CardSuit getSuit();
  CardValue getValue();
  bool isColorCard(bool includeBlack);
  unsigned int getScore(CardSuit tableColor);
};