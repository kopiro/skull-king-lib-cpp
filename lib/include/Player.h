#include "Card.h"
#include <vector>

class Player {
private:
  std::vector<Card *> hand;

public:
  Player();
  void addCardToHand(Card *card);
  void resetHand();
};