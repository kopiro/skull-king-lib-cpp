#pragma once

#include "Card.h"
#include "Player.h"
#include <map>
#include <vector>
class Game {
private:
  unsigned short round = 0;
  std::vector<Player *> players;
  std::vector<Card *> deck;
  std::vector<std::pair<Card *, Player *>> table;
  std::map<Player *, unsigned int> score;

  void createShuffledDeck();
  Card *dealCard();

  Card *getWinningCard(Card *beforeCard, Card *afterCard, CardSuit tableColor);

public:
  Game();
  void addPlayer(Player *player);
  void startNewRound();
  void addCardToTable(Card *card, Player *player);
  std::pair<Card *, Player *> determineWinner();
};