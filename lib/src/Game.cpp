#include "Game.h"
#include "Card.h"
#include "Round.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

Game::Game(std::vector<Player *> _players) : players(_players) {
  for (const auto player : players) {
    gameScore[player] = 0;
  }
}

void Game::startNewRound() {
  currentRound =
      new Round(currentRound == NULL ? 1 : currentRound->cardCount + 1, players,
                gameScore, startingRoundPlayerIndex);
}

void Game::closeRound() {
  gameScore = currentRound->closeRound();
  startingRoundPlayerIndex = (startingRoundPlayerIndex + 1) % players.size();
}
