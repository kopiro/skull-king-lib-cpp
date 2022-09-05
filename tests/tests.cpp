#include "Player.h"
#include "SkullKingLib.h"
#include <gtest/gtest.h>

TEST(SkullKingDeck, Assert52Cards) {
  std::vector<Player *> players;
  players.push_back(new Player("A"));
  players.push_back(new Player("B"));
  players.push_back(new Player("C"));
  auto game = new Game(players);
  auto deck = game->createShuffledDeck();
  EXPECT_EQ(deck.size(), 78);
}