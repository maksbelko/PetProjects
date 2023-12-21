#include "handStrenghtOraganizer.h"
#include <algorithm>
#include <iostream>

handStrenghtOrganizer::handStrenghtOrganizer(){};

finalHand handStrenghtOrganizer::calcHandStrenght(vector<Card> hand,
                                                  vector<Card> board) {
  if (hand.size() != 2) {
    throw "cannot calc because hand.size() is not 2";
  } else if (board.size() != 5) {
    throw "cannot calc because board.size() is not 5";
  }
  board.push_back(hand.front());
  board.push_back(hand.back());
  board = this->sortBoard(board);

  if (isStrFlush(board)) {
    vector<Card> kickers;
    int clubs = 0;
    int spades = 0;
    int hearts = 0;
    int diamonds = 0;
    for (auto i = board.begin(); i != board.end(); i++) {
      switch (i->suit) {
      case Suit::Spades:
        spades++;
        break;
      case Suit::Hearts:
        hearts++;
        break;
      case Suit::Clubs:
        clubs++;
        break;
      case Suit::Diamonds:
        diamonds++;
        break;
      default:
        throw "Unknown suit of card";
        break;
      }
    }
    Suit flshSuit;
    if (spades >= 5) {
      flshSuit = Suit::Spades;
    }
    if (clubs >= 5) {
      flshSuit = Suit::Clubs;
    }
    if (hearts >= 5) {
      flshSuit = Suit::Hearts;
    }
    if (diamonds >= 5) {
      flshSuit = Suit::Diamonds;
    }

    auto card = board.begin();
    int sameSuitCards = std::max({diamonds, hearts, clubs, spades});
    while (board.size() > sameSuitCards) {
      if (static_cast<int>(card->suit) != static_cast<int>(flshSuit)) {
        board.erase(card);
        card = board.begin();
      }
      card = board.end() == card ? board.begin() : card + 1;
    }

    int strFlushCards = 1;
    int startIndex;
    int endIndex;
    int index = 0;
    int valueOfCard = static_cast<int>(board.begin()->value);
    for (auto i = board.begin(); i != board.end(); i++) {
      if ((valueOfCard - static_cast<int>(i->value)) == 1) {
        if (strFlushCards == 1) {
          startIndex = index;
        }
        strFlushCards++;
        if (strFlushCards == 5) {
          endIndex = index;
          break;
        }
      } else if ((valueOfCard - static_cast<int>(i->value)) > 1) {
        strFlushCards = 1;
      }

      if (i->value == Value::two && strFlushCards == 4 &&
          board.front().value == Value::ace) {
        strFlushCards++;
        endIndex = 1;
        break;
      }
      valueOfCard = static_cast<int>(i->value);
      index++;
    }
    if (endIndex > startIndex) {
      for (int i = 0; i < 5; i++) {
        kickers.push_back(*(board.begin() + startIndex + i - 1));
      }
    } else {
      kickers.push_back(board.front());
      for (int i = 0; i < 4; i++) {
        kickers.push_back(*(board.end() - i - 1));
      }
    }
    return finalHand(9, kickers);
  } else if (isFourOfAKind(board)) {
    vector<Card> kickers;
    int sameValueCards = 1;
    int currentCardValue = static_cast<int>(board.begin()->value);
    int startIndex = 0;
    int endIndex = 0;
    int index = 1;
    auto currentCard = board.begin();
    while (currentCard + 1 != board.end()) {
      if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
        if (sameValueCards == 1) {
          startIndex = index;
        }
        sameValueCards++;
      } else {
        currentCardValue = static_cast<int>((currentCard + 1)->value);
        sameValueCards = 1;
      }
      if (sameValueCards == 4) {
        endIndex = index;
        break;
      }
      index++;
      currentCard = currentCard + 1;
    }
    for (int i = 0; i < 4; i++) {
      kickers.push_back(*(board.begin() + startIndex - 1));
      board.erase(board.begin() + startIndex - 1);
    }
    kickers.push_back(board.front());
    return finalHand(8, kickers);
  } else if (isFullHouse(board)) {
    vector<Card> kickers;
    int setStartIndex = 0;
    int index = 1;
    int sameValueCards = 1;
    int currentCardValue = static_cast<int>(board.begin()->value);
    auto currentCard = board.begin();
    while (currentCard + 1 != board.end()) {
      if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
        if (sameValueCards == 1) {
          setStartIndex = index;
        }
        sameValueCards++;
      } else {
        currentCardValue = static_cast<int>((currentCard + 1)->value);
        sameValueCards = 1;
      }
      if (sameValueCards == 3) {
        break;
      }
      currentCard = currentCard + 1;
      index++;
    }

    for (int i = 0; i < 3; i++) {
      kickers.push_back(*(board.begin() + setStartIndex - 1));
      board.erase(board.begin() + setStartIndex - 1);
    }
    currentCard = board.begin();
    index = 1;
    int pairStartIndex = 0;
    while (currentCard + 1 != board.end()) {
      if (static_cast<int>((currentCard + 1)->value) ==
          static_cast<int>(currentCard->value)) {
        pairStartIndex = index;
        break;
      } else {
        currentCardValue = static_cast<int>((currentCard + 1)->value);
      }
      currentCard = currentCard + 1;
      index++;
    }

    for (int i = 0; i < 2; i++) {
      kickers.push_back(*(board.begin() + pairStartIndex - 1));
      board.erase(board.begin() + pairStartIndex - 1);
    }
    return finalHand(7, kickers);
  } else if (isFlush(board)) {
    vector<Card> kickers;
    int clubs = 0;
    int spades = 0;
    int hearts = 0;
    int diamonds = 0;

    int valueOfCard = static_cast<int>(board.front().value);
    int cardsInARow = 1;
    for (auto i = board.begin(); i != board.end(); i++) {
      switch (i->suit) {
      case Suit::Spades:
        spades++;
        break;
      case Suit::Hearts:
        hearts++;
        break;
      case Suit::Clubs:
        clubs++;
        break;
      case Suit::Diamonds:
        diamonds++;
        break;
      default:
        throw "Unknown suit of card";
        break;
      }
    }
    Suit flshSuit;
    if (spades >= 5) {
      flshSuit = Suit::Spades;
    }
    if (clubs >= 5) {
      flshSuit = Suit::Clubs;
    }
    if (hearts >= 5) {
      flshSuit = Suit::Hearts;
    }
    if (diamonds >= 5) {
      flshSuit = Suit::Diamonds;
    }
    auto card = board.begin();
    int sameSuitCards = std::max({diamonds, hearts, clubs, spades});
    while (board.size() > sameSuitCards) {
      if (static_cast<int>(card->suit) != static_cast<int>(flshSuit)) {
        board.erase(card);
        card = board.begin();
      };
      if (card == (board.end() - 1)) {
        break;
      } else {
        card++;
      }
    }
    for (int i = 0; i < 5; i++) {
      kickers.push_back(board.front());
      board.erase(board.begin());
    }
    return finalHand(6, kickers);
  } else if (isStr(board)) {
    vector<Card> kickers;
    int startIndex = 0;
    int endIndex = 0;
    int strCards = 1;
    int index = 0;
    int valueOfCard = static_cast<int>(board.begin()->value);
    for (auto i = board.begin(); i != board.end(); i++) {
      if ((valueOfCard - static_cast<int>(i->value)) == 1) {
        if (strCards == 1) {
          startIndex = index;
        }
        strCards++;
        if (strCards == 5) {
          endIndex = index;
          break;
        }
      } else if ((valueOfCard - static_cast<int>(i->value)) > 1) {
        strCards = 1;
      }

      if (i->value == Value::two && strCards == 4 &&
          board.front().value == Value::ace) {
        strCards++;
        endIndex = 1;
        break;
      }
      valueOfCard = static_cast<int>(i->value);
      index++;
    }
    if (endIndex > startIndex) {
      for (int i = 0; i < 5; i++) {
        kickers.push_back(*(board.begin() + startIndex + i - 1));
      }
    } else {
      kickers.push_back(board.front());
      for (int i = 0; i < 4; i++) {
        kickers.push_back(*(board.end() - i - 1));
      }
    }
    return finalHand(5, kickers);
  } else if (isSet(board)) {
    vector<Card> kickers;
    int setStartIndex = 0;
    int index = 1;
    int sameValueCards = 1;
    int currentCardValue = static_cast<int>(board.begin()->value);
    auto currentCard = board.begin();
    while (currentCard + 1 != board.end()) {
      if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
        if (sameValueCards == 1) {
          setStartIndex = index;
        }
        sameValueCards++;
      } else {
        currentCardValue = static_cast<int>((currentCard + 1)->value);
        sameValueCards = 1;
      }
      if (sameValueCards == 3) {
        break;
      }
      currentCard = currentCard + 1;
      index++;
    }
    for (int i = 0; i < 3; i++) {
      kickers.push_back(*(board.begin() + setStartIndex - 1));
      board.erase(board.begin() + setStartIndex - 1);
    }
    for (int i = 0; i < 2; i++) {
      kickers.push_back(board.front());
      board.erase(board.begin());
    }
    return finalHand(4, kickers);
  } else if (isTwoPairs(board)) {
    vector<Card> kickers;
    int pairStartIndex = 0;
    int index = 1;
    int sameValueCards = 1;
    int currentCardValue = static_cast<int>(board.begin()->value);
    auto currentCard = board.begin();
    while (currentCard + 1 != board.end()) {
      if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
        pairStartIndex = index;
        break;
      } else {
        currentCardValue = static_cast<int>((currentCard + 1)->value);
      }
      currentCard = currentCard + 1;
      index++;
    }
    for (int i = 0; i < 2; i++) {
      kickers.push_back(*(board.begin() + pairStartIndex - 1));
      board.erase(board.begin() + pairStartIndex - 1);
    }
    pairStartIndex = 0;
    index = 1;
    sameValueCards = 1;
    currentCardValue = static_cast<int>(board.begin()->value);
    currentCard = board.begin();
    while (currentCard + 1 != board.end()) {
      if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
        pairStartIndex = index;
        break;
      } else {
        currentCardValue = static_cast<int>((currentCard + 1)->value);
      }
      currentCard = currentCard + 1;
      index++;
    }
    for (int i = 0; i < 2; i++) {
      kickers.push_back(*(board.begin() + pairStartIndex - 1));
      board.erase(board.begin() + pairStartIndex - 1);
    }
    kickers.push_back(board.front());

    return finalHand(3, kickers);
  } else if (isPair(board)) {
    vector<Card> kickers;
    int pairStartIndex = 0;
    int index = 1;
    int sameValueCards = 1;
    int currentCardValue = static_cast<int>(board.begin()->value);
    auto currentCard = board.begin();
    while (currentCard + 1 != board.end()) {
      if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
        pairStartIndex = index;
        break;
      } else {
        currentCardValue = static_cast<int>((currentCard + 1)->value);
      }
      currentCard = currentCard + 1;
      index++;
    }
    for (int i = 0; i < 2; i++) {
      kickers.push_back(*(board.begin() + pairStartIndex - 1));
      board.erase(board.begin() + pairStartIndex - 1);
    }
    for (int i = 0; i < 3; i++) {
      kickers.push_back(board.front());
      board.erase(board.begin());
    }

    return finalHand(2, kickers);
  } else {
    vector<Card> kickers;
    for (int i = 0; i < 5; i++) {
      kickers.push_back(board.front());
      board.erase(board.begin());
    }
    return finalHand(1, kickers);
  }
}

vector<Card> handStrenghtOrganizer::sortBoard(vector<Card> board) {
  if (board.size() != 7) {
    throw "cannot calc because board.size() is not 7";
  }
  vector<Card> sortedBoard;
  int index = 0;
  int highestCardIndex = 0;
  Card biggest;
  auto biggestPos = board.begin();
  int maxValue = 1;
  while (board.size() > 0) {
    for (auto i = board.begin(); i != board.end(); i++) {
      if (static_cast<int>(i->value) > maxValue) {
        maxValue = static_cast<int>(i->value);
        biggest = *i;
        biggestPos = i;
      }
    }
    maxValue = 1;
    sortedBoard.push_back(biggest);
    board.erase(biggestPos);
  }
  return sortedBoard;
}

bool handStrenghtOrganizer::isStrFlush(vector<Card> hand) {
  int clubs = 0;
  int spades = 0;
  int hearts = 0;
  int diamonds = 0;
  bool hasStraight = false;
  int valueOfCard = static_cast<int>(hand.front().value);
  int cardsInARow = 1;
  for (auto i = hand.begin(); i != hand.end(); i++) {
    switch (i->suit) {
    case Suit::Spades:
      spades++;
      break;
    case Suit::Hearts:
      hearts++;
      break;
    case Suit::Clubs:
      clubs++;
      break;
    case Suit::Diamonds:
      diamonds++;
      break;
    default:
      throw "Unknown suit of card";
      break;
    }
    if ((valueOfCard - static_cast<int>(i->value)) == 1) {
      cardsInARow++;
      if (cardsInARow == 5) {
        hasStraight = true;
      }
    } else if ((valueOfCard - static_cast<int>(i->value)) > 1) {
      cardsInARow = 1;
    }
    valueOfCard = static_cast<int>(i->value);
    if (i->value == Value::two && cardsInARow == 4 &&
        hand.front().value == Value::ace) {
      hasStraight = true;
    }
  }
  if (!((hearts >= 5 || spades >= 5 || clubs >= 5 || diamonds >= 5) &&
        hasStraight)) {
    return false;
  }
  Suit flshSuit;
  if (spades >= 5) {
    flshSuit = Suit::Spades;
  }
  if (clubs >= 5) {
    flshSuit = Suit::Clubs;
  }
  if (hearts >= 5) {
    flshSuit = Suit::Hearts;
  }
  if (diamonds >= 5) {
    flshSuit = Suit::Diamonds;
  }

  auto card = hand.begin();
  int sameSuitCards = std::max({diamonds, hearts, clubs, spades});
  while (hand.size() > sameSuitCards) {
    if (static_cast<int>(card->suit) != static_cast<int>(flshSuit)) {
      hand.erase(card);
      card = hand.begin();
    }
    if (card == (hand.end() - 1)) {
      break;
    } else {
      card++;
    }
  }

  int strFlushCards = 1;
  valueOfCard = static_cast<int>(hand.begin()->value);
  for (auto i = hand.begin(); i != hand.end(); i++) {
    if ((valueOfCard - static_cast<int>(i->value)) == 1) {
      strFlushCards++;
      if (strFlushCards == 5) {
        return true;
      }
    } else if ((valueOfCard - static_cast<int>(i->value)) > 1) {
      strFlushCards = 1;
    }
    valueOfCard = static_cast<int>(i->value);
    if (i->value == Value::two && strFlushCards == 4 &&
        hand.front().value == Value::ace) {
      return true;
    }
  }
  return false;
}
bool handStrenghtOrganizer::isFourOfAKind(vector<Card> hand) {
  int sameValueCards = 1;
  int currentCardValue = static_cast<int>(hand.begin()->value);
  auto currentCard = hand.begin();
  while (currentCard + 1 != hand.end()) {
    if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
      sameValueCards++;
    } else {
      currentCardValue = static_cast<int>((currentCard + 1)->value);
      sameValueCards = 1;
    }
    if (sameValueCards == 4) {
      return true;
    }
    currentCard = currentCard + 1;
  }
  return false;
}
bool handStrenghtOrganizer::isFullHouse(vector<Card> hand) {

  bool hasSet = false;
  bool hasPair = false;
  int sameValueCards = 1;
  int currentCardValue = static_cast<int>(hand.begin()->value);
  auto currentCard = hand.begin();
  while (currentCard + 1 != hand.end()) {
    if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
      sameValueCards++;
    } else {
      currentCardValue = static_cast<int>((currentCard + 1)->value);
      sameValueCards = 1;
    }
    if (sameValueCards == 2) {
      hasPair = true;
    }
    if (sameValueCards == 3) {
      if (hasSet == true) {
        break;
      } else {
        hasSet = true;
        hasPair = false;
      }
    }
    currentCard = currentCard + 1;
  }

  return hasPair && hasSet;
}
bool handStrenghtOrganizer::isFlush(vector<Card> hand) {
  int clubs = 0;
  int spades = 0;
  int hearts = 0;
  int diamonds = 0;

  int valueOfCard = static_cast<int>(hand.front().value);
  int cardsInARow = 1;
  for (auto i = hand.begin(); i != hand.end(); i++) {
    switch (i->suit) {
    case Suit::Spades:
      spades++;
      break;
    case Suit::Hearts:
      hearts++;
      break;
    case Suit::Clubs:
      clubs++;
      break;
    case Suit::Diamonds:
      diamonds++;
      break;
    default:
      throw "Unknown suit of card";
      break;
    }
  }
  return std::max({diamonds, clubs, spades, hearts}) >= 5;
}
bool handStrenghtOrganizer::isStr(vector<Card> hand) {

  int valueOfCard = static_cast<int>(hand.front().value);
  int cardsInARow = 1;
  for (auto i = hand.begin(); i != hand.end(); i++) {
    if ((valueOfCard - static_cast<int>(i->value)) == 1) {
      cardsInARow++;
      if (cardsInARow == 5) {
        return true;
      }
    } else if ((valueOfCard - static_cast<int>(i->value)) > 1) {
      cardsInARow = 1;
    }
    valueOfCard = static_cast<int>(i->value);
    if (i->value == Value::two && cardsInARow == 4 &&
        hand.front().value == Value::ace) {
      return true;
    }
  }
  return false;
  ;
}

bool handStrenghtOrganizer::isSet(vector<Card> hand) {

  int sameValueCards = 1;
  int currentCardValue = static_cast<int>(hand.begin()->value);
  auto currentCard = hand.begin();
  while (currentCard + 1 != hand.end()) {
    if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
      sameValueCards++;
      if (sameValueCards == 3) {
        return true;
      }
    } else {
      currentCardValue = static_cast<int>((currentCard + 1)->value);
      sameValueCards = 1;
    }
    currentCard = currentCard + 1;
  }
  return false;
}
bool handStrenghtOrganizer::isTwoPairs(vector<Card> hand) {
  int pairsCount = 0;
  int sameValueCards = 1;
  int currentCardValue = static_cast<int>(hand.begin()->value);
  auto currentCard = hand.begin();
  while (currentCard + 1 != hand.end()) {
    if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
      sameValueCards++;
    } else {
      currentCardValue = static_cast<int>((currentCard + 1)->value);
      sameValueCards = 1;
    }
    if (sameValueCards == 2) {
      pairsCount++;
    }
    currentCard = currentCard + 1;
  }

  return pairsCount >= 2;
}
bool handStrenghtOrganizer::isPair(vector<Card> hand) {
  int currentCardValue = static_cast<int>(hand.begin()->value);
  auto currentCard = hand.begin();
  while (currentCard + 1 != hand.end()) {
    if (static_cast<int>((currentCard + 1)->value) == currentCardValue) {
      return true;
    } else {
      currentCardValue = static_cast<int>((currentCard + 1)->value);
    }
    currentCard = currentCard + 1;
  }
  return false;
}
