#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "Round.h"
#include <gtest/gtest.h>

TEST(SkullKingDeck, CardCount) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->startNewRound();
  EXPECT_EQ(game->currentRound->createShuffledDeck().size(), 79);
}

TEST(SkullKingDeck, WhiteflagLosing) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0], new Card(green, one));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(whiteflag, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[2], new Card(red, two));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[0]], 0);
}

TEST(SkullKingDeck, BiggerColorTableWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0], new Card(green, two));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(green, three));
  game->currentRound->dealCardToPlayer(game->players[2], new Card(green, one));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[0]], 0);
}

TEST(SkullKingDeck, OnlyColorTableWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0], new Card(green, one));
  game->currentRound->dealCardToPlayer(game->players[1], new Card(red, three));
  game->currentRound->dealCardToPlayer(game->players[2],
                                       new Card(yellow, three));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[0]], 0);
}

TEST(SkullKingDeck, BiggerBlackWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0], new Card(green, ten));
  game->currentRound->dealCardToPlayer(game->players[1], new Card(black, nine));
  game->currentRound->dealCardToPlayer(game->players[2], new Card(black, two));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[1]], 0);
}

TEST(SkullKingDeck, PirateWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0], new Card(green, ten));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(pirate, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[2], new Card(black, two));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[1]], 0);
}

TEST(SkullKingDeck, FirstPirateCardWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0],
                                       new Card(pirate, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(pirate, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[2],
                                       new Card(pirate, SPECIAL));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[0]], 0);
}

TEST(SkullKingDeck, MermaidWinningOverKing) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0], new Card(green, ten));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(mermaid, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[2],
                                       new Card(king, SPECIAL));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[1]], 50);
}

TEST(SkullKingDeck, KingWinningOverTwoPirates) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0],
                                       new Card(pirate, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(king, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[2],
                                       new Card(pirate, SPECIAL));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[1]], 60);
}

TEST(SkullKingDeck, MermaidWinningOverKingAndPirate) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0],
                                       new Card(pirate, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(mermaid, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[2],
                                       new Card(king, SPECIAL));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 1);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 0);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[1]], 50);
}

TEST(SkullKingDeck, LastWhiteflagLosingInAllWhiteflagsTable) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->currentRound->dealCardToPlayer(game->players[0],
                                       new Card(whiteflag, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[1],
                                       new Card(whiteflag, SPECIAL));
  game->currentRound->dealCardToPlayer(game->players[2],
                                       new Card(whiteflag, SPECIAL));
  game->startNewRound();
  game->currentRound->startNewTable();
  game->currentRound->playCardFromPlayer(game->players[0],
                                         game->players[0]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[1],
                                         game->players[1]->hand[0]);
  game->currentRound->playCardFromPlayer(game->players[2],
                                         game->players[2]->hand[0]);
  game->currentRound->closeTable();
  game->currentRound->clearPlayerHands();

  EXPECT_EQ(game->currentRound->tableVictories[game->players[0]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[1]], 0);
  EXPECT_EQ(game->currentRound->tableVictories[game->players[2]], 1);
  EXPECT_EQ(game->currentRound->additionalTablesScore[game->players[2]], 0);
}
