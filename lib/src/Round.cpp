#include "Round.h"
#include "Card.h"
#include "Player.h"
#include <exception>
#include <map>
#include <random>
#include <stdexcept>
#include <unordered_map>

static const unsigned short kColorCardCount = 13;
static const unsigned short kPirateCount = 5;
static const unsigned short kMermaidCount = 2;
static const unsigned short kKingCount = 1;
static const unsigned short kWhiteflagCount = 5;
static const unsigned short kPirateOrWhiteflagCount = 1;
static const CardSuit suits[] = {green, blue, red, yellow, black};

Round::Round(unsigned short _cardCount, std::vector<Player *> _players,
             std::map<Player *, short> _gameScore)
    : cardCount(_cardCount), players(_players), gameScore(_gameScore) {
  this->deck = this->createShuffledDeck();

  for (const auto player : this->players) {
    this->tablesWins[player] = 0;
    this->additionalTablesScore[player] = 0;
  }
}

std::vector<Card *> Round::createShuffledDeck() {
  std::vector<Card *> deck;

  // Create color cards
  for (const CardSuit suit : suits) {
    for (unsigned short value = 1; value <= kColorCardCount; value++) {
      deck.push_back(new Card(suit, static_cast<CardValue>(value)));
    }
  }
  for (unsigned short count = 0; count < kWhiteflagCount; count++) {
    deck.push_back(new Card(whiteflag, SPECIAL));
  }
  for (unsigned short count = 0; count < kPirateCount; count++) {
    deck.push_back(new Card(pirate, SPECIAL));
  }
  for (unsigned short count = 0; count < kMermaidCount; count++) {
    deck.push_back(new Card(mermaid, SPECIAL));
  }
  for (unsigned short count = 0; count < kKingCount; count++) {
    deck.push_back(new Card(mermaid, SPECIAL));
  }
  for (unsigned short count = 0; count < kKingCount; count++) {
    deck.push_back(new Card(pirateOrWhiteflag, SPECIAL));
  }

  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(deck), std::end(deck), rng);

  return deck;
}

void Round::setBetForPlayer(Player *player, unsigned short bet) {
  if (bet > this->cardCount) {
    throw std::invalid_argument("Bet can't be more than cardCount");
  }
  this->playerBets[player] = bet;
}

void Round::addCardToTable(Player *player, Card *card) {
  this->table.push_back(std::make_pair(player, card));
}

Card *Round::dealCardFromDeck() {
  Card *card = this->deck.back();
  this->deck.pop_back();
  return card;
}

std::pair<Card *, unsigned short>
Round::getWinningCard(Card *beforeCard, Card *afterCard, CardSuit tableColor,
                      Card *maybeMermaidOnTable) {
  if (beforeCard == NULL) {
    return std::make_pair(afterCard, 0);
  }

  // Mermaid-King case to get additional 50 points
  if (maybeMermaidOnTable != NULL && afterCard->suit == king) {
    return std::make_pair(maybeMermaidOnTable, 50);
  }
  if (beforeCard->suit == mermaid && afterCard->suit == king) {
    return std::make_pair(beforeCard, 50);
  }
  if (beforeCard->suit == king && afterCard->suit == mermaid) {
    return std::make_pair(afterCard, 50);
  }

  // King-Pirate case to get additional 30 points
  if (beforeCard->suit == king && afterCard->suit == pirate) {
    return std::make_pair(beforeCard, 30);
  }

  if (beforeCard->suit == pirate && afterCard->suit == king) {
    return std::make_pair(afterCard, 30);
  }

  // In all other cases, we get a score based on current-color and compare that
  // This will clearly determine the winning card.. unless score is the same
  unsigned int beforeCardScore = beforeCard->getScore(tableColor);
  unsigned int afterCardScore = afterCard->getScore(tableColor);
  if (beforeCardScore > afterCardScore)
    return std::make_pair(beforeCard, 0);
  if (beforeCardScore < afterCardScore)
    return std::make_pair(afterCard, 0);

  // If they are both same color cards, compare the values
  if (beforeCard->isColorCard(true) && afterCard->isColorCard(true) &&
      beforeCard->suit == afterCard->suit) {
    if (beforeCard->value > afterCard->value)
      return std::make_pair(beforeCard, 0);
    if (beforeCard->value < afterCard->value)
      return std::make_pair(afterCard, 0);
    assert("Invariant violation: trying to compare same color card, but "
           "duplicates shouldn't exists");
  }

  // In case they are same score, LEFT card always wins
  // this handles the:
  // - pirate case
  // - mermaid case
  // - king case (even though only 1 is in the deck)
  // - white flag (in reverse)
  if (beforeCard->suit == whiteflag) {
    return std::make_pair(afterCard, 0);
  }

  return std::make_pair(beforeCard, 0);
}

std::pair<Player *, unsigned short> Round::determineTableWinner() {
  CardSuit tableColor = UNKNOWN;

  Card *winningCard = NULL;
  unsigned short additionalPoints = 0;

  Card *maybeMermaidOnTable = NULL;

  std::unordered_map<Card *, Player *> cardToPlayer;

  for (auto const &[player, card] : this->table) {
    cardToPlayer[card] = player;

    // Determine the color of the table by getting the first color appearing
    if (tableColor == UNKNOWN && card->isColorCard(true)) {
      tableColor = card->suit;
    }

    if (maybeMermaidOnTable == NULL && card->suit == mermaid) {
      maybeMermaidOnTable = card;
    }

    auto newWinningCard = this->getWinningCard(winningCard, card, tableColor,
                                               maybeMermaidOnTable);

    if (newWinningCard.first != winningCard) {
      // Reset points if the winning card changed
      additionalPoints = 0;
    }

    winningCard = newWinningCard.first;
    // Add points from his new winning card (ex: multiple pirates)
    additionalPoints += newWinningCard.second;
  }

  return std::make_pair(cardToPlayer[winningCard], additionalPoints);
}

void Round::incrementTableWins() {
  auto winningPlayer = this->determineTableWinner();
  this->tablesWins[winningPlayer.first]++;
  this->additionalTablesScore[winningPlayer.first] += winningPlayer.second;
}

void Round::dealCards() {
  for (const auto player : this->players) {
    for (auto i = 0; i < this->cardCount; i++) {
      player->addCardToHand(this->dealCardFromDeck());
    }
  }
}

void Round::startNewTable() {
  this->tableCount++;
  this->table.clear();
}

std::map<Player *, short> Round::determineNewGameScore() {
  if (this->tableCount != this->cardCount) {
    throw std::logic_error("Round is not finished yet to calculate bets score");
  }

  for (const auto player : this->players) {
    const auto playerBet = this->playerBets[player];
    const auto tablesWins = this->tablesWins[player];

    if (playerBet == 0) {
      // Lose all
      if (tablesWins == 0) {
        this->gameScore[player] += this->cardCount;
      } else {
        this->gameScore[player] -= this->cardCount;
      }
    } else {
      // Win something
      const auto diff = abs(tablesWins - playerBet);
      if (diff == 0) {
        this->gameScore[player] +=
            (20 * playerBet) + this->additionalTablesScore[player];
      } else {
        this->gameScore[player] -= 10 * diff;
      }
    }
  }

  return this->gameScore;
}