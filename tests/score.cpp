#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "Round.h"
#include <gtest/gtest.h>

TEST(SkullKingScore, TestRound1) {
  const auto game =
      new Game({new Player("A"), new Player("B"), new Player("C")});

  game->startNewRound();

  auto r = game->currentRound;
  EXPECT_EQ(r->cardCount, 1);

  const auto p0GreenOne0 = new Card(green, one);
  const auto p1Whiteflag0 = new Card(whiteflag, SPECIAL);
  const auto p2Pirate0 = new Card(pirate, SPECIAL);

  r->dealCardToPlayer(game->players[0], p0GreenOne0);
  r->dealCardToPlayer(game->players[1], p1Whiteflag0);
  r->dealCardToPlayer(game->players[2], p2Pirate0);

  r->setBetForPlayer(game->players[0], 1); // (actual = 0)
  r->setBetForPlayer(game->players[1], 0); // (actual = 0)
  r->setBetForPlayer(game->players[2], 1); // (actual = 1)

  r->startNewTable();
  r->playCardFromPlayer(game->players[0], p0GreenOne0);
  r->playCardFromPlayer(game->players[1], p1Whiteflag0);
  r->playCardFromPlayer(game->players[2], p2Pirate0);
  r->closeTable();

  game->closeRound();

  EXPECT_EQ(game->gameScore[game->players[0]], -10);
  EXPECT_EQ(game->gameScore[game->players[1]], 10);
  EXPECT_EQ(game->gameScore[game->players[2]], 20);
}

TEST(SkullKingScore, TestRound2) {
  const auto game =
      new Game({new Player("A"), new Player("B"), new Player("C")});

  game->startNewRound();
  auto r1 = game->currentRound;

  EXPECT_EQ(r1->cardCount, 1);

  const auto r0p0Pirate0 = new Card(pirate, SPECIAL);
  const auto r0p1King0 = new Card(king, SPECIAL);
  const auto r0p2Whiteflag0 = new Card(whiteflag, SPECIAL);

  r1->dealCardToPlayer(game->players[0], r0p0Pirate0);
  r1->dealCardToPlayer(game->players[1], r0p1King0);
  r1->dealCardToPlayer(game->players[2], r0p2Whiteflag0);

  r1->setBetForPlayer(game->players[0],
                      1); // (actual = 0)
  r1->setBetForPlayer(game->players[1],
                      1); // (actual = 1)
  r1->setBetForPlayer(game->players[2],
                      0); // (actual = 0)

  r1->startNewTable();
  r1->playCardFromPlayer(game->players[0], r0p0Pirate0);
  r1->playCardFromPlayer(game->players[1], r0p1King0);
  r1->playCardFromPlayer(game->players[2], r0p2Whiteflag0);
  r1->closeTable();

  r1->clearPlayerHands();
  game->closeRound();

  EXPECT_EQ(game->gameScore[game->players[0]], -10);
  EXPECT_EQ(game->gameScore[game->players[1]], 30 + 20);
  EXPECT_EQ(game->gameScore[game->players[2]], 10);

  game->startNewRound();
  auto r2 = game->currentRound;
  EXPECT_EQ(r2->cardCount, 2);

  const auto r1p0Pirate0 = new Card(pirate, SPECIAL);
  const auto r1p0GreenTwo = new Card(green, two);
  const auto r1p1GreenThree = new Card(green, three);
  const auto r1p1RedFour = new Card(red, four);
  const auto r1p2King0 = new Card(king, SPECIAL);
  const auto r1p2Pirate0 = new Card(pirate, SPECIAL);

  r2->dealCardToPlayer(game->players[0], r1p0Pirate0);
  r2->dealCardToPlayer(game->players[0], r1p0GreenTwo);

  r2->dealCardToPlayer(game->players[1], r1p1GreenThree);
  r2->dealCardToPlayer(game->players[1], r1p1RedFour);

  r2->dealCardToPlayer(game->players[2], r1p2King0);
  r2->dealCardToPlayer(game->players[2], r1p2Pirate0);

  r2->setBetForPlayer(game->players[0], 1); // (actual = 0, so -10)
  r2->setBetForPlayer(game->players[1], 0); // (actual = 0, so +20)
  r2->setBetForPlayer(game->players[2],
                      2); // (actual = 2, so +40 +(30 for pirate))

  r2->startNewTable();
  r2->playCardFromPlayer(game->players[0], r1p0GreenTwo);
  r2->playCardFromPlayer(game->players[1], r1p1GreenThree);
  r2->playCardFromPlayer(game->players[2],
                         r1p2King0); // winner, no extra points
  r2->closeTable();

  r2->startNewTable();
  // player 2 starts now
  r2->playCardFromPlayer(game->players[2],
                         r1p2Pirate0); // winner
  r2->playCardFromPlayer(game->players[0], r1p0Pirate0);
  r2->playCardFromPlayer(game->players[1], r1p1RedFour);
  r2->closeTable();

  r2->clearPlayerHands();
  game->closeRound();

  EXPECT_EQ(game->gameScore[game->players[0]], -10 - 10);
  EXPECT_EQ(game->gameScore[game->players[1]], 50 + 20);
  EXPECT_EQ(game->gameScore[game->players[2]], 10 + 20 + 20);
}
