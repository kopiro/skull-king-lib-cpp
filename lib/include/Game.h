#pragma once

#include "Card.h"
#include "Player.h"
#include <vector>

class Game {
private:
  unsigned short round = 0;
  std::vector<Player *> players;
  std::vector<Card *> deck;

  void createDeck();
  Card *dealCard();

public:
  Game();
  void addPlayer(Player *player);
  void startNewRound();
};