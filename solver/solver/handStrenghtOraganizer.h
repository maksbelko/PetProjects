#ifndef HANDSTRENGHTORGANIZER_H
#define HANDSTRENGHTORGANIZER_H
#include "Types.cpp"
#include <vector>

class handStrenghtOrganizer {
public:
  handStrenghtOrganizer();
  finalHand calcHandStrenght(vector<Card> hand, vector<Card> board);
  vector<Card> sortBoard(vector<Card>);
  bool isStrFlush(vector<Card> hand);
  bool isFourOfAKind(vector<Card> hand);
  bool isFullHouse(vector<Card> hand);
  bool isFlush(vector<Card> hand);
  bool isStr(vector<Card> hand);
  bool isSet(vector<Card> hand);
  bool isTwoPairs(vector<Card> hand);
  bool isPair(vector<Card> hand);
};
#endif // !HANDSTRENGHTORGANIZER_H
