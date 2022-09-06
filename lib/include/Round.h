#pragma once

#include "Card.h"
#include "Player.h"
#include <map>
#include <vector>

class Round {
private:
public:
  Round(unsigned short _cardCount, std::vector<Player *> _players,
        std::map<Player *, short> _gameScore,
        unsigned short _startingPlayerIndex);

  std::vector<Player *> players;
  std::vector<std::pair<Player *, Card *>> table;
  std::map<Player *, unsigned short> playerBets;
  std::map<Player *, short> gameScore;
  std::vector<Card *> deck;
  std::map<Player *, unsigned short> tableVictories;
  std::map<Player *, unsigned short> additionalTablesScore;

  Player *nextPlayingPlayer;

  unsigned short cardCount;
  unsigned short tableIndex = 0;

  void setBetForPlayer(Player *player, unsigned short bet);
  void playCardFromPlayer(Player *player, Card *card);
  void dealCardToPlayer(Player *player, Card *card);
  void clearPlayerHands();

  std::pair<Card *, unsigned short> getWinningCard(Card *beforeCard,
                                                   Card *afterCard,
                                                   CardSuit tableColor,
                                                   Card *mermaidOnTable);

  std::vector<Card *> createShuffledDeck();
  Card *dealCardFromDeck();
  void dealCardsToPlayers();

  std::pair<Player *, unsigned short> determineTableWinner();

  void startNewTable();
  void closeTable();

  std::map<Player *, short> closeRound();
};