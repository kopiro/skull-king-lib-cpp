#include "Game.h"
#include "Card.h"
#include "Round.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

Game::Game(std::vector<Player *> _players) : players(_players) {
  for (const auto player : this->players) {
    this->gameScore[player] = 0;
  }
  this->round = new Round(0, players, this->gameScore);
}

Round *Game::startNewRound() {
  this->round =
      new Round(this->round->cardCount + 1, this->players, this->gameScore);
  return this->round;
}
