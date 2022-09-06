#include "Card.h"
#include "Game.h"
#include "Player.h"
#include "Round.h"
#include <gtest/gtest.h>

TEST(SkullKingDeck, AssertCardCount) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  auto round = game->startNewRound();
  EXPECT_EQ(round->createShuffledDeck().size(), 79);
}

TEST(SkullKingDeck, AssertWhiteflagLosing) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, one));
  game->players[1]->addCardToHand(new Card(whiteflag, SPECIAL));
  game->players[2]->addCardToHand(new Card(red, two));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[0]);
  EXPECT_EQ(winner.second, 0);
}

TEST(SkullKingDeck, AssertBiggerColorTableWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, two));
  game->players[1]->addCardToHand(new Card(green, three));
  game->players[2]->addCardToHand(new Card(green, one));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[1]);
  EXPECT_EQ(winner.second, 0);
}

TEST(SkullKingDeck, AssertOnlyColorTableWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, one));
  game->players[1]->addCardToHand(new Card(red, three));
  game->players[2]->addCardToHand(new Card(yellow, three));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[0]);
  EXPECT_EQ(winner.second, 0);
}

TEST(SkullKingDeck, AssertBiggerBlackWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, ten));
  game->players[1]->addCardToHand(new Card(black, nine));
  game->players[2]->addCardToHand(new Card(black, two));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[1]);
  EXPECT_EQ(winner.second, 0);
}

TEST(SkullKingDeck, AssertPirateWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, ten));
  game->players[1]->addCardToHand(new Card(pirate, SPECIAL));
  game->players[2]->addCardToHand(new Card(black, two));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[1]);
  EXPECT_EQ(winner.second, 0);
}

TEST(SkullKingDeck, AssertFirstPirateCardWinning) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, ten));
  game->players[1]->addCardToHand(new Card(pirate, SPECIAL));
  game->players[2]->addCardToHand(new Card(mermaid, SPECIAL));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[1]);
  EXPECT_EQ(winner.second, 0);
}

TEST(SkullKingDeck, AssertMermaidWinningOverKing) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(green, ten));
  game->players[1]->addCardToHand(new Card(mermaid, SPECIAL));
  game->players[2]->addCardToHand(new Card(king, SPECIAL));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[1]);
  EXPECT_EQ(winner.second, 50);
}

TEST(SkullKingDeck, AssertKingWinningOverTwoPirates) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(pirate, SPECIAL));
  game->players[1]->addCardToHand(new Card(king, SPECIAL));
  game->players[2]->addCardToHand(new Card(pirate, SPECIAL));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[1]);
  EXPECT_EQ(winner.second, 60);
}

TEST(SkullKingDeck, AssertMermaidWinningOverKingAndPirate) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(pirate, SPECIAL));
  game->players[1]->addCardToHand(new Card(mermaid, SPECIAL));
  game->players[2]->addCardToHand(new Card(king, SPECIAL));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[1]);
  EXPECT_EQ(winner.second, 50);
}

TEST(SkullKingDeck, AssertLastWhiteflagLosingInAllWhiteflagsTable) {
  auto game = new Game({new Player("A"), new Player("B"), new Player("C")});
  game->players[0]->addCardToHand(new Card(whiteflag, SPECIAL));
  game->players[1]->addCardToHand(new Card(whiteflag, SPECIAL));
  game->players[2]->addCardToHand(new Card(whiteflag, SPECIAL));
  auto round = game->startNewRound();
  round->startNewTable();
  round->addCardToTable(game->players[0], game->players[0]->hand[0]);
  round->addCardToTable(game->players[1], game->players[1]->hand[0]);
  round->addCardToTable(game->players[2], game->players[2]->hand[0]);
  auto winner = round->determineTableWinner();
  EXPECT_EQ(winner.first, game->players[2]);
  EXPECT_EQ(winner.second, 0);
}
