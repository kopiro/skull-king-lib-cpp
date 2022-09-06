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
  return this->startRoundNumber(this->round->cardCount + 1);
}

Round *Game::startRoundNumber(unsigned short cardCount) {
  this->round = new Round(cardCount, this->players, this->gameScore);
  return this->round;
}

void Game::closeRound() { this->gameScore = this->round->closeRound(); }
