#pragma once

#include "Card.h"
#include "Player.h"
#include <map>
#include <vector>
class Game {
private:
  unsigned short round = 0;
  std::vector<Player *> players;

public:
  Game(std::vector<Player *> _players);
  Card *dealCardFromDeck(std::vector<Card *> deck);
  Card *getWinningCard(Card *beforeCard, Card *afterCard, CardSuit tableColor);
  std::vector<Card *> createShuffledDeck();
  std::vector<std::pair<Player *, Card *>> startNewRound();
  void addCardToTable(std::vector<std::pair<Player *, Card *>> table,
                      Card *card, Player *player);
  std::pair<Player *, Card *>
  determineTableWinner(std::vector<std::pair<Player *, Card *>> table);
};