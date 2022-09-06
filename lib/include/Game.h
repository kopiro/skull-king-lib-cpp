#pragma once

#include "Card.h"
#include "Player.h"
#include "Round.h"
#include <map>
#include <vector>
class Game {
private:
public:
  Round *round;
  std::vector<Player *> players;
  std::map<Player *, short> gameScore;

  Game(std::vector<Player *> _players);
  Round *startNewRound();
  Round *startRoundNumber(unsigned short cardCount);
  void closeRound();
};