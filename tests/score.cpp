#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "Round.h"
#include <gtest/gtest.h>

TEST(SkullKingScore, TestA) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, one));
  game->players[1]->addCardToHand(new Card(whiteflag, SPECIAL));
  game->players[2]->addCardToHand(new Card(pirate, two));
  game->startNewRound();
  game->round->setBetForPlayer(game->players[0], 1);
  game->round->setBetForPlayer(game->players[1], 0);
  game->round->setBetForPlayer(game->players[2], 1);
  game->round->startNewTable();
  game->round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  game->round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  game->round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  game->round->closeTable();
  game->closeRound();
  EXPECT_EQ(game->gameScore[game->players[0]], -10);
  EXPECT_EQ(game->gameScore[game->players[1]], 10);
  EXPECT_EQ(game->gameScore[game->players[2]], 20);
}

TEST(SkullKingScore, TestB) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});

  game->startNewRound();
  EXPECT_EQ(game->round->cardCount, 1);

  game->players[0]->addCardToHand(new Card(pirate, SPECIAL));
  game->players[1]->addCardToHand(new Card(king, SPECIAL));
  game->players[2]->addCardToHand(new Card(whiteflag, SPECIAL));
  game->round->setBetForPlayer(game->players[0], 1);
  game->round->setBetForPlayer(game->players[1], 1);
  game->round->setBetForPlayer(game->players[2], 0);
  game->round->startNewTable();
  game->round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  game->round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  game->round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  game->round->closeTable();
  game->closeRound();
  game->players[0]->clearHand();
  game->players[1]->clearHand();
  game->players[2]->clearHand();

  EXPECT_EQ(game->gameScore[game->players[0]], -10);
  EXPECT_EQ(game->gameScore[game->players[1]], 50);
  EXPECT_EQ(game->gameScore[game->players[2]], 10);

  game->startNewRound();
  EXPECT_EQ(game->round->cardCount, 2);

  game->players[0]->addCardToHand(new Card(pirate, SPECIAL));
  game->players[0]->addCardToHand(new Card(green, two));

  game->players[1]->addCardToHand(new Card(green, three));
  game->players[1]->addCardToHand(new Card(red, four));

  game->players[2]->addCardToHand(new Card(king, SPECIAL));
  game->players[2]->addCardToHand(new Card(whiteflag, SPECIAL));

  game->round->setBetForPlayer(game->players[0], 1);
  game->round->setBetForPlayer(game->players[1], 0);
  game->round->setBetForPlayer(game->players[2], 1);

  game->round->startNewTable();
  game->round->addCardToTable(game->players[0],
                              game->players[0]->hand[1]); // g2
  game->round->addCardToTable(game->players[1],
                              game->players[1]->hand[0]); // g3
  game->round->addCardToTable(game->players[2], game->players[2]->hand[1]); // w
  game->round->closeTable(); // wins1

  game->round->startNewTable();
  game->round->addCardToTable(game->players[0], game->players[0]->hand[0]); // p
  game->round->addCardToTable(game->players[1],
                              game->players[1]->hand[1]); // r4
  game->round->addCardToTable(game->players[2], game->players[2]->hand[0]); // k
  game->round->closeTable(); // wins2

  game->closeRound();

  game->players[0]->clearHand();
  game->players[1]->clearHand();
  game->players[2]->clearHand();

  EXPECT_EQ(game->gameScore[game->players[0]], -10 - 10);
  EXPECT_EQ(game->gameScore[game->players[1]], 50 - 20);
  EXPECT_EQ(game->gameScore[game->players[2]], 10 + 50);
}
