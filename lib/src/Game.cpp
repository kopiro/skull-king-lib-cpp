#include "Game.h"
#include "Card.h"
#include <algorithm>
#include <cassert>
#include <random>
#include <utility>
#include <vector>

Game::Game(std::vector<Player *> _players) : players(_players) {}

static const unsigned short kColorCardCount = 13;
static const unsigned short kPirateCount = 5;
static const unsigned short kMermaidCount = 2;
static const unsigned short kKingCount = 2;
static const unsigned short kWhiteflagCount = 5;
static const unsigned short kPirateOrWhiteflagCount = 1;
static const CardSuit suits[] = {CardSuit::green, CardSuit::blue, CardSuit::red,
                                 CardSuit::yellow, CardSuit::black};

std::vector<Card *> Game::createShuffledDeck() {
  std::vector<Card *> deck;

  // Create color cards
  for (const CardSuit suit : suits) {
    for (unsigned short value = 1; value <= kColorCardCount; value++) {
      deck.push_back(new Card(suit, static_cast<CardValue>(value)));
    }
  }
  for (unsigned short count = 0; count < kWhiteflagCount; count++) {
    deck.push_back(new Card(whiteflag, CardValue::special));
  }
  for (unsigned short count = 0; count < kPirateCount; count++) {
    deck.push_back(new Card(pirate, CardValue::special));
  }
  for (unsigned short count = 0; count < kMermaidCount; count++) {
    deck.push_back(new Card(mermaid, CardValue::special));
  }
  for (unsigned short count = 0; count < kKingCount; count++) {
    deck.push_back(new Card(mermaid, CardValue::special));
  }
  for (unsigned short count = 0; count < kKingCount; count++) {
    deck.push_back(new Card(pirateOrWhiteflag, CardValue::special));
  }

  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(deck), std::end(deck), rng);

  return deck;
}

Card *Game::dealCardFromDeck(std::vector<Card *> deck) {
  Card *card = deck.back();
  deck.pop_back();
  return card;
}

std::vector<std::pair<Player *, Card *>> Game::startNewRound() {
  std::vector<Card *> deck = this->createShuffledDeck();
  std::vector<std::pair<Player *, Card *>> table;

  this->round++;

  for (const auto player : players) {
    for (unsigned short i = 0; i < round; i++) {
      player->addCardToHand(this->dealCardFromDeck(deck));
    }
  }

  return table;
}

void Game::addCardToTable(std::vector<std::pair<Player *, Card *>> table,
                          Card *card, Player *player) {
  table.push_back(std::make_pair(player, card));
}

Card *Game::getWinningCard(Card *beforeCard, Card *afterCard,
                           CardSuit tableColor) {
  // Mermaid always wins over King even though has less score, so check this
  // before the score-based checks
  if (beforeCard->getSuit() == mermaid && afterCard->getSuit() == king)
    return beforeCard;

  if (beforeCard->getSuit() == king && afterCard->getSuit() == mermaid)
    return afterCard;

  // In all other cases, we get a score based on current-color and compare that
  // This will clearly determine the winning card.. unless score is the same
  unsigned int beforeCardScore = beforeCard->getScore(tableColor);
  unsigned int afterCardScore = afterCard->getScore(tableColor);
  if (beforeCardScore > afterCardScore)
    return beforeCard;
  if (beforeCardScore < afterCardScore)
    return afterCard;

  // If they are both same color cards, compare the values
  if (beforeCard->isColorCard(true) && afterCard->isColorCard(true) &&
      beforeCard->getSuit() == afterCard->getSuit()) {
    unsigned int beforeCardValue = beforeCard->getValue();
    unsigned int afterCardValue = afterCard->getValue();
    if (beforeCardValue > afterCardValue)
      return beforeCard;
    if (beforeCardValue < afterCardValue)
      return afterCard;
    assert("Invariant violation: trying to compare same color card, but "
           "duplicates shouldn't exists");
  }

  // In case they are same score, LEFT card always wins
  // this handles the:
  // - pirate case
  // - mermaid case
  // - king case (even though only 1 is in the deck)
  // - white flag (in reverse)
  if (beforeCard->getSuit() == whiteflag)
    return afterCard;
  return beforeCard;
}

std::pair<Player *, Card *>
Game::determineTableWinner(std::vector<std::pair<Player *, Card *>> table) {
  CardSuit tableColor = UNKNOWN;
  std::pair<Player *, Card *> winner;

  for (auto const &[player, card] : table) {
    if (tableColor == UNKNOWN && card->isColorCard(true)) {
      tableColor = card->getSuit();
    }
    if (winner.first == NULL ||
        card == getWinningCard(winner.second, card, tableColor)) {
      winner.first = player;
      winner.second = card;
    }
  }

  return winner;
}