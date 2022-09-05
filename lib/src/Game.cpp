#include "Game.h"
#include "Card.h"
#include <algorithm>
#include <cassert>
#include <random>
#include <utility>
#include <vector>

Game::Game() {}

static const unsigned short kColorCardCount = 13;
static const unsigned short kPirateCount = 5;
static const unsigned short kMermaidCount = 2;
static const unsigned short kKingCount = 2;
static const unsigned short kWhiteflagCount = 2;
static const unsigned short kPirateOrWhiteflagCount = 1;
static const CardSuit suits[] = {CardSuit::green, CardSuit::blue, CardSuit::red,
                                 CardSuit::yellow, CardSuit::black};

void Game::createShuffledDeck() {
  deck.clear();

  // Create color cards
  for (const CardSuit suit : suits) {
    for (unsigned short value = 1; value <= kColorCardCount; value++) {
      deck.push_back(new Card(suit, static_cast<CardValue>(value)));
    }
  }
  for (unsigned short count = 0; count < kWhiteflagCount; count++) {
    deck.push_back(new Card(CardSuit::whiteflag, CardValue::special));
  }
  for (unsigned short count = 0; count < kPirateCount; count++) {
    deck.push_back(new Card(CardSuit::pirate, CardValue::special));
  }
  for (unsigned short count = 0; count < kMermaidCount; count++) {
    deck.push_back(new Card(CardSuit::mermaid, CardValue::special));
  }
  for (unsigned short count = 0; count < kKingCount; count++) {
    deck.push_back(new Card(CardSuit::mermaid, CardValue::special));
  }
  for (unsigned short count = 0; count < kKingCount; count++) {
    deck.push_back(new Card(CardSuit::pirateOrWhiteflag, CardValue::special));
  }

  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(deck), std::end(deck), rng);
}

Card *Game::dealCard() {
  Card *card = deck.back();
  deck.pop_back();
  return card;
}

void Game::startNewRound() {
  round++;
  table.clear();
  createShuffledDeck();
  for (const auto player : players) {
    for (unsigned short i = 0; i < round; i++) {
      player->addCardToHand(dealCard());
    }
  }
}

void Game::addPlayer(Player *player) { players.push_back(player); }

void Game::addCardToTable(Card *card, Player *player) {
  table.push_back(std::make_pair(card, player));
}

Card *Game::getWinningCard(Card *beforeCard, Card *afterCard,
                           CardSuit tableColor) {
  // Mermaid always wins over King even though has less score, so check this
  // before the score-based checks
  if (beforeCard->getSuit() == CardSuit::mermaid &&
      afterCard->getSuit() == CardSuit::king)
    return beforeCard;

  if (beforeCard->getSuit() == CardSuit::king &&
      afterCard->getSuit() == CardSuit::mermaid)
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
  if (beforeCard->getSuit() == CardSuit::whiteflag)
    return afterCard;
  return beforeCard;
}

std::pair<Card *, Player *> Game::determineWinner() {
  CardSuit tableColor = UNKNOWN;
  std::pair<Card *, Player *> winner;

  for (auto const &[card, player] : table) {
    if (tableColor == UNKNOWN && card->isColorCard(true)) {
      tableColor = card->getSuit();
    }
    if (winner.first == NULL ||
        card == getWinningCard(winner.first, card, tableColor)) {
      winner.first = card;
      winner.second = player;
    }
  }

  return winner;
}