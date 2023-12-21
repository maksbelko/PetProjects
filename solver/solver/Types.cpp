#ifndef TYPES
#define TYPES
#include <string>
#include <vector>
enum class Suit { Diamonds = 0, Hearts = 1, Clubs = 2, Spades = 3 };
enum class Value {
  two = 2,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  ten,
  jack,
  queen,
  king,
  ace
};
using namespace std;
struct Card {
  Suit suit;
  Value value;
  Card() {
    suit = Suit::Diamonds;
    value = Value::queen;
  }
  Card(Value _value, Suit _suit) {
    suit = _suit;
    value = _value;
  };
  Card(char _value, char _suit) {
    switch (_value) {
    case '2':
      value = Value::two;
      break;
    case '3':
      value = Value::three;
      break;
    case '4':
      value = Value::four;
      break;
    case '5':
      value = Value::five;
      break;
    case '6':
      value = Value::six;
      break;
    case '7':
      value = Value::seven;
      break;
    case '8':
      value = Value::eight;
      break;
    case '9':
      value = Value::nine;
      break;
    case 'T':
      value = Value::ten;
      break;
    case 'J':
      value = Value::jack;
      break;
    case 'Q':
      value = Value::queen;
      break;
    case 'K':
      value = Value::king;
      break;
    case 'A':
      value = Value::ace;
      break;
    default:
      throw "Unknown Value of card";
      break;
    }
    switch (_suit) {
    case 's':
      suit = Suit::Spades;
      break;
    case 'h':
      suit = Suit::Hearts;
      break;
    case 'c':
      suit = Suit::Clubs;
      break;
    case 'd':
      suit = Suit::Diamonds;
      break;
    default:
      throw "Unknown suit of card";
      break;
    }
  }
  Card(string str) { *this = Card(*str.begin(), *(str.begin() + 1)); }
};
// TODO add enum of hands strenghts
struct finalHand {
  int strenght = 1;     // straight-flush - 9, kicker - 1;
  vector<Card> kickers; // lenght - 5
  finalHand(int strenght, vector<Card> kickers) {
    this->strenght = strenght;
    this->kickers = kickers;
  }
  inline bool operator<(finalHand &o) {
    if (this->strenght < o.strenght) {
      return true;
    } else {
      return false;
    }
  }
  inline bool operator>(finalHand &o) {
    if (this->strenght > o.strenght) {
      return true;
    } else {
      return false;
    }
  }
};
// KKKQQ QQQKK

#endif // !TYPES
