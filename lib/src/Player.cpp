#include "Player.h"
#include "Round.h"
#include <stdexcept>

Player::Player(std::string _name) : name(_name) {}

void Player::addCardToHand(Card *card) { hand.push_back(card); }

void Player::clearHand() { hand.clear(); }

void Player::removeCardFromHand(Card *card) {
  auto it = std::find(hand.begin(), hand.end(), card);
  if (it == hand.end()) {
    throw std::invalid_argument("Can't find this card in the player's hand");
  }
  hand.erase(it);
}