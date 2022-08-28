#include "Game.h"
#include "Card.h"
#include <algorithm>
#include <random>
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

void Game::createDeck() {
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
  createDeck();
  for (const auto player : players) {
    for (unsigned short i = 0; i < round; i++) {
      player->addCardToHand(dealCard());
    }
  }
}

void Game::addPlayer(Player *player) { players.push_back(player); }
