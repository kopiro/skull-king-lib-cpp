#pragma once

#include "Card.h"
#include "Player.h"
#include "Round.h"
#include <map>
#include <vector>
class Game {
private:
public:
  Round *currentRound = NULL;
  std::vector<Player *> players;
  std::map<Player *, short> gameScore;
  unsigned short startingRoundPlayerIndex = 0;

  Game(std::vector<Player *> _players);
  void startNewRound();
  void closeRound();
};