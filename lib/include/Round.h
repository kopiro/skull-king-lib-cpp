#pragma once

#include "Card.h"
#include "Player.h"
#include <map>
#include <vector>

class Round {
private:
  std::vector<Player *> players;
  std::vector<std::pair<Player *, Card *>> table;
  std::map<Player *, unsigned short> playerBets;
  std::map<Player *, unsigned short> tablesWins;
  std::map<Player *, unsigned short> additionalTablesScore;
  std::map<Player *, short> gameScore;

public:
  Round(unsigned short _cardCount, std::vector<Player *> _players,
        std::map<Player *, short> _gameScore);

  std::vector<Card *> deck;

  unsigned short cardCount;
  unsigned short tableCount = 0;

  void setBetForPlayer(Player *player, unsigned short bet);
  void addCardToTable(Player *player, Card *card);

  std::pair<Card *, unsigned short> getWinningCard(Card *beforeCard,
                                                   Card *afterCard,
                                                   CardSuit tableColor,
                                                   Card *mermaidOnTable);

  std::vector<Card *> createShuffledDeck();
  Card *dealCardFromDeck();
  void dealCards();

  std::pair<Player *, unsigned short> determineTableWinner();
  void closeTable();

  void startNewTable();

  std::map<Player *, short> closeRound();
};