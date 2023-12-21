// solver.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
#include "Types.cpp"
#include "handStrenghtOraganizer.h"
#include "valueOrganizer.h"
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
vector<Card> fillDeck();
string ParseCard(Card);
int main() {
  static vector<Card> deck = fillDeck();
  for (auto i = deck.begin(); i != deck.end(); i++) {
    cout << ParseCard(*i) << " ";
  }
  cout << endl;
  vector<Card> heroHand;
  vector<Card> board;
  heroHand.push_back(Card("As"));
  heroHand.push_back(Card("Ks"));
  /*for (auto i = heroHand.begin(); i != heroHand.end(); i++) {
          cout << ParseCard(*i) << " ";
  }*/
  // vector<Card> opHand;
  // opHand.push_back(Card('A', 'd'));
  // opHand.push_back(Card('K', 'd'));

  // board.push_back(Card('A', 'h'));
  // board.push_back(Card('7', 'd'));
  // board.push_back(Card('5', 'c'));
  // board.push_back(Card('T', 'd'));
  // board.push_back(Card('3', 'c'));
  // board.push_back(hand.front());
  // board.push_back(hand.back());
  handStrenghtOrganizer org;
  // cards on board
  string boardStr = "Ah,7d,5c,9h";
  // all the combinations that could be in opponent hand

  // the enum of combinations
  string opRange =
      "AcKc,AcQc,AcJc,AcTc,AcKh,AcKs,AsKh,AsKc,KcKh,KsKh,KcQc,KcJc,KcTc,AcQh,"
      "AcQs,AsQh,AsQc,KhQc,KhQd,KhQs,KcQh,KcQd,KcQs,KsQh,KsQc,QcQh,QsQh,QcJc,"
      "QcTc,AcJh,AcJs,AsJh,AsJc,KhJc,KhJd,KhJs,KcJh,KcJd,KcJs,KsJh,KsJc";
  string heroHandStr = "Ad,Kd";

  /*vector<Card> fullBoard = org.sortBoard(board);
  for (auto i = fullBoard.begin(); i != fullBoard.end(); i++) {
          cout << ParseCard(*i) << " ";
  }

  cout << "All cards:\n";
  fullBoard = org.sortBoard(board);
  for (auto i = fullBoard.begin(); i != fullBoard.end(); i++) {
          cout << ParseCard(*i) << " ";
  }*/

  /*bool isStrFlush = org.isStrFlush(board);
  cout << "\nResult :";
  cout << isStrFlush << endl;
  */
  /*bool isFourOfAKind = org.isFourOfAKind(board);
  cout << "\nResult :";
  cout << isFourOfAKind << endl;
  */
  /*bool isFullHouse = org.isFullHouse(board);
  cout << "\nResult :";
  cout << isFullHouse << endl;
  */
  /*finalHand fh = org.calcHandStrenght(heroHand, board);
  for (auto i = fh.kickers.begin(); i != fh.kickers.end(); i++) {
          cout << ParseCard(*i) << " ";
  }*/
  valueOrganizer vo;

  // to make board empty or filled
  // board.push_back(Card("Ah"));
  // board.push_back(Card("7d"));
  // board.push_back(Card("5c"));
  clock_t start = clock();
  cout << "Timer starts" << endl;
  // remove cards that already in deck
  deck = vo.cutDeck(deck, board);
  // cout << "Cards in deck:" << endl;
  // for (auto i = deck.begin(); i != deck.end(); i++) {
  //   cout << ParseCard(*i) << " ";
  // }
  // cout << endl;
  double win = vo.compareHandVSRange(heroHandStr, opRange, boardStr);
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  cout << endl << "Equity vs range: " << win << "\nTime spent: " << seconds;

  // operators
  //  vector<Card> finalHandOp;
  //  vector<Card> finalHandHero;
  //  finalHandHero.push_back(Card('A', 'd'));
  //  finalHandHero.push_back(Card('A', 's'));
  //  finalHandHero.push_back(Card('A', 'c'));
  //  finalHandHero.push_back(Card('K', 'd'));
  //  finalHandHero.push_back(Card('2', 'c'));
  //  finalHandOp.push_back(Card('A', 'd'));
  //  finalHandOp.push_back(Card('A', 's'));
  //  finalHandOp.push_back(Card('K', 'd'));
  //  finalHandOp.push_back(Card('2', 'c'));
  //  finalHandOp.push_back(Card('3', 's'));
  //  finalHand hero1(4, finalHandHero);
  //  finalHand op1(3, finalHandOp);
  //  cout << (hero1 < op1);
  //  cout << (hero1 > op1);
}

vector<Card> fillDeck() {
  vector<Card> deck;
  int value = 2;
  int suit = 0;
  while (value <= 14) {
    while (suit <= 3) {
      deck.push_back(Card(static_cast<Value>(value), static_cast<Suit>(suit)));
      suit++;
    };
    value++;
    suit = 0;
  }
  return deck;
}

string ParseCard(Card card) {
  string cardSpelling = "";
  switch (card.value) {
  case Value::ten:
    cardSpelling += "T";
    break;
  case Value::jack:
    cardSpelling += "J";
    break;
  case Value::queen:
    cardSpelling += "Q";
    break;
  case Value::king:
    cardSpelling += "K";
    break;
  case Value::ace:
    cardSpelling += "A";
    break;
  default:
    cardSpelling += char('0' + static_cast<int>(card.value));
    break;
  }
  switch (card.suit) {
  case Suit::Diamonds:
    cardSpelling += "d";
    break;
  case Suit::Clubs:
    cardSpelling += "c";
    break;
  case Suit::Hearts:
    cardSpelling += "h";
    break;
  case Suit::Spades:
    cardSpelling += "s";
    break;
  default:
    break;
  }
  return cardSpelling;
};

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
