#ifndef VALUE_ORGANIZER
#define VALUE_ORGANIZER
#include "Types.cpp"
#include "handStrenghtOraganizer.h"
#include <iostream>
#include <string>
#include <vector>

class valueOrganizer {

private:
  handStrenghtOrganizer org;
  vector<Card> fillDeck() {
    vector<Card> deck;
    int value = 2;
    int suit = 0;
    while (value <= 14) {
      while (suit <= 3) {
        deck.push_back(
            Card(static_cast<Value>(value), static_cast<Suit>(suit)));
        suit++;
      };
      value++;
      suit = 0;
    }
    return deck;
  }
  double compairStrFlushes(finalHand &const, finalHand &const);
  double compair4OfAKinds(finalHand &const, finalHand &const);
  double compairFullHouses(finalHand &const, finalHand &const);
  double compairFlushes(finalHand &const, finalHand &const);
  double compairStraigts(finalHand &const, finalHand &const);
  double compair3OfAKinds(finalHand &const, finalHand &const);
  double compair2Pairs(finalHand &const, finalHand &const);
  double compairPairs(finalHand &const, finalHand &const);
  double compairKickers(finalHand &const, finalHand &const);

public:
  valueOrganizer();
  string ParseCard(Card);
  vector<string> split(string s, string del);
  vector<Card> cutDeck(vector<Card> deck, vector<Card> cardsToCut);
  double CompareHands(vector<Card> heroHand, vector<Card> opHand,
                      vector<Card> board);
  double compareHandVSRange(string heroHand, string opRange, string board);
};

#endif // !VALUE_ORGANIZER
