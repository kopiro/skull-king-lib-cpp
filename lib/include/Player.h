#pragma once

#include "Card.h"
#include <string>
#include <vector>

class Player {
private:
  std::vector<Card *> hand;
  std::string name;

public:
  Player(std::string name);
  void addCardToHand(Card *card);
  void resetHand();
};