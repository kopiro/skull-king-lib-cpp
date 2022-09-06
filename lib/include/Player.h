#pragma once

#include "Card.h"
#include <string>
#include <vector>

class Player {
public:
  std::string name;
  std::vector<Card *> hand;

  Player(std::string name);
  void addCardToHand(Card *card);
  void clearHand();
};