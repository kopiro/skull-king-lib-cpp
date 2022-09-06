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
             std::map<Player *, short> _gameScore,
             unsigned short _startingRoundPlayerIndex)
    : cardCount(_cardCount), players(_players), gameScore(_gameScore) {
  deck = createShuffledDeck();

  for (const auto player : players) {
    tableVictories[player] = 0;
    additionalTablesScore[player] = 0;
  }

  nextPlayingPlayer = players.at(_startingRoundPlayerIndex);
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
    deck.push_back(new Card(UNKNOWN, PIRATE_OR_WHITE_FLAG));
  }

  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(deck), std::end(deck), rng);

  return deck;
}

void Round::setBetForPlayer(Player *player, unsigned short bet) {
  if (bet > cardCount) {
    throw std::invalid_argument("Bet can't be more than cardCount");
  }
  playerBets[player] = bet;
}

void Round::playCardFromPlayer(Player *player, Card *card) {
  if (nextPlayingPlayer != player) {
    throw std::logic_error("Order of players playing has not been respected");
  }

  auto playerIt = std::find(players.begin(), players.end(), nextPlayingPlayer);
  if (playerIt == players.end()) {
    throw std::logic_error("Can't find this player in the list of all players");
  }

  player->removeCardFromHand(card);
  table.push_back(std::make_pair(player, card));

  nextPlayingPlayer =
      players.at((playerIt - players.begin() + 1) % players.size());
}

Card *Round::dealCardFromDeck() {
  Card *card = deck.back();
  deck.pop_back();
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
  unsigned int beforeCardScore = beforeCard->getRank(tableColor);
  unsigned int afterCardScore = afterCard->getRank(tableColor);
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

  // Oh gosh - the mermaid could be not the winning card in the loop ('cause
  // it's been defeated by a pirate before), so we need to keep a reference to
  // first mermaid encoutered in the table so we can always make the battle
  // between KING and MERMAID and proclaim the mermaid as the winner
  Card *maybeMermaidOnTable = NULL;

  std::unordered_map<Card *, Player *> cardToPlayerMap;

  for (auto const &[player, card] : table) {
    cardToPlayerMap[card] = player;

    // Determine the color of the table by getting the first color appearing
    if (tableColor == UNKNOWN && card->isColorCard(true)) {
      tableColor = card->suit;
    }

    if (maybeMermaidOnTable == NULL && card->suit == mermaid) {
      maybeMermaidOnTable = card;
    }

    auto newWinningCard =
        getWinningCard(winningCard, card, tableColor, maybeMermaidOnTable);

    if (newWinningCard.first != winningCard) {
      // Reset points if the winning card changed
      additionalPoints = 0;
    }

    winningCard = newWinningCard.first;
    // Add points from his new winning card (ex: multiple pirates)
    additionalPoints += newWinningCard.second;
  }

  return std::make_pair(cardToPlayerMap[winningCard], additionalPoints);
}

void Round::clearPlayerHands() {
  for (const auto player : players) {
    player->clearHand();
  }
}

void Round::closeTable() {
  auto winningPlayer = determineTableWinner();
  // Next playing player is the winner of this table
  nextPlayingPlayer = winningPlayer.first;
  tableVictories[winningPlayer.first]++;
  additionalTablesScore[winningPlayer.first] += winningPlayer.second;
}

void Round::dealCardsToPlayers() {
  for (const auto player : players) {
    for (auto i = 0; i < cardCount; i++) {
      player->addCardToHand(dealCardFromDeck());
    }
  }
}

void Round::startNewTable() {
  if (tableIndex == cardCount) {
    throw std::logic_error("Calling startNewTable without enough cardCount");
  }

  tableIndex++;
  table.clear();
}

void Round::dealCardToPlayer(Player *player, Card *card) {
  player->addCardToHand(card);
}

std::map<Player *, short> Round::closeRound() {
  if (tableIndex != cardCount) {
    throw std::logic_error("Calling closeRound too soon");
  }

  for (const auto player : players) {
    const auto playerBet = playerBets[player];
    const auto tableVictory = tableVictories[player];

    if (playerBet == 0) {
      // Lose all
      if (tableVictory == 0) {
        gameScore[player] += 10 * cardCount;
      } else {
        gameScore[player] -= 10 * cardCount;
      }
    } else {
      // Win something
      const auto diff = abs(tableVictory - playerBet);
      if (diff == 0) {
        gameScore[player] += (20 * playerBet) + additionalTablesScore[player];
      } else {
        gameScore[player] -= 10 * diff;
      }
    }
  }

  return gameScore;
}