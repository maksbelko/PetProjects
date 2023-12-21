#include "valueOrganizer.h"

valueOrganizer::valueOrganizer() { org = handStrenghtOrganizer(); }

string valueOrganizer::ParseCard(Card card) {
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
vector<string> valueOrganizer::split(string s, string del = ",") {
  vector<string> cards;
  int start = 0;
  int end = s.find(del);
  while (end != -1) {
    cards.push_back(s.substr(start, end - start));
    start = end + del.size();
    end = s.find(del, start);
  }
  cards.push_back(s.substr(start, end - start));
  return cards;
}
vector<Card> valueOrganizer::cutDeck(vector<Card> deck,
                                     vector<Card> cardsToCut) {
  int cardsToRemove = cardsToCut.size();
  auto deckIt = deck.begin();
  bool isErased = false;

  while (cardsToRemove > 0) {
    for (auto i = cardsToCut.begin(); i != cardsToCut.end(); i++) {
      if (static_cast<int>(i->suit) == static_cast<int>(deckIt->suit) &&
          static_cast<int>(i->value) == static_cast<int>(deckIt->value)) {
        deckIt = deck.erase(deckIt);
        cardsToRemove--;
        isErased = true;
        if (cardsToRemove == 0) {
          break;
        }
      }
    }
    if (cardsToRemove == 0) {
      break;
    }
    if (isErased) {
      isErased = false;
      continue;
    }
    if (deckIt + 1 == deck.end()) {
      break;
    }
    deckIt++;
  }
  return deck;
}
// returns 1 if hero wins, 0 if op wins, 0.5 if draw
double valueOrganizer::compairStrFlushes(finalHand &const hero,
                                         finalHand &const op) {
  return static_cast<int>(hero.kickers.back().value) >
                 static_cast<int>(op.kickers.back().value)
             ? 1
         : static_cast<int>(hero.kickers.back().value) ==
                 static_cast<int>(op.kickers.back().value)
             ? 0.5
             : 0;
}
double valueOrganizer::compair4OfAKinds(finalHand &const hero,
                                        finalHand &const op) {
  if (static_cast<int>(hero.kickers.front().value) >
      static_cast<int>(op.kickers.front().value)) {
    return 1;
  } else if (static_cast<int>(hero.kickers.front().value) <
             static_cast<int>(op.kickers.front().value)) {
    return 0;
  } else {
    return static_cast<int>(hero.kickers.back().value) >
                   static_cast<int>(op.kickers.back().value)
               ? 1
           : static_cast<int>(hero.kickers.back().value) ==
                   static_cast<int>(op.kickers.back().value)
               ? 0.5
               : 0;
  }
}
double valueOrganizer::compairFullHouses(finalHand &const hero,
                                         finalHand &const op) {
  if (static_cast<int>(hero.kickers.front().value) >
      static_cast<int>(op.kickers.front().value)) {
    return 1;
  } else if (static_cast<int>(hero.kickers.front().value) <
             static_cast<int>(op.kickers.front().value)) {
    return 0;
  } else {
    return static_cast<int>(hero.kickers.back().value) >
                   static_cast<int>(op.kickers.back().value)
               ? 1
           : static_cast<int>(hero.kickers.back().value) ==
                   static_cast<int>(op.kickers.back().value)
               ? 0.5
               : 0;
  }
}
double valueOrganizer::compairFlushes(finalHand &const hero,
                                      finalHand &const op) {
  for (int i = 0; i < 5; i++) {
    if (static_cast<int>((*(hero.kickers.begin() + i)).value) >
        static_cast<int>((*(op.kickers.begin() + i)).value)) {
      return 1;
    } else if (static_cast<int>((*(hero.kickers.begin() + i)).value) <
               static_cast<int>((*(op.kickers.begin() + i)).value)) {
      return 0;
    }
  }
  return 0.5;
}

double valueOrganizer::compairStraigts(finalHand &const hero,
                                       finalHand &const op) {
  return static_cast<int>(hero.kickers.back().value) >
                 static_cast<int>(op.kickers.back().value)
             ? 1
         : static_cast<int>(hero.kickers.back().value) ==
                 static_cast<int>(op.kickers.back().value)
             ? 0.5
             : 0;
}
double valueOrganizer::compair3OfAKinds(finalHand &const hero,
                                        finalHand &const op) {
  if (static_cast<int>(hero.kickers.front().value) >
      static_cast<int>(op.kickers.front().value)) {
    return 1;
  } else if (static_cast<int>(hero.kickers.front().value) <
             static_cast<int>(op.kickers.front().value)) {
    return 0;
  } else {
    for (int i = 3; i < 5; i++) {
      if (static_cast<int>((*(hero.kickers.begin() + i)).value) >
          static_cast<int>((*(op.kickers.begin() + i)).value)) {
        return 1;
      } else if (static_cast<int>((*(hero.kickers.begin() + i)).value) <
                 static_cast<int>((*(op.kickers.begin() + i)).value)) {
        return 0;
      }
    }
    return 0.5;
  }
}

double valueOrganizer::compair2Pairs(finalHand &const hero,
                                     finalHand &const op) {
  if (static_cast<int>(hero.kickers.front().value) >
      static_cast<int>(op.kickers.front().value)) {
    return 1;
  } else if (static_cast<int>(hero.kickers.front().value) <
             static_cast<int>(op.kickers.front().value)) {
    return 0;
  } else if (static_cast<int>((hero.kickers.begin() + 2)->value) >
             static_cast<int>((op.kickers.begin() + 2)->value)) {
    return 1;
  } else if (static_cast<int>((hero.kickers.begin() + 2)->value) <
             static_cast<int>((op.kickers.begin() + 2)->value)) {
    return 0;
  } else {
    return static_cast<int>(hero.kickers.back().value) >
                   static_cast<int>(op.kickers.back().value)
               ? 1
           : static_cast<int>(hero.kickers.back().value) ==
                   static_cast<int>(op.kickers.back().value)
               ? 0.5
               : 0;
  }
}
double valueOrganizer::compairPairs(finalHand &const hero,
                                    finalHand &const op) {
  if (static_cast<int>(hero.kickers.front().value) >
      static_cast<int>(op.kickers.front().value)) {
    return 1;
  } else if (static_cast<int>(hero.kickers.front().value) <
             static_cast<int>(op.kickers.front().value)) {
    return 0;
  } else {
    for (int i = 2; i < 5; i++) {
      if (static_cast<int>((*(hero.kickers.begin() + i)).value) >
          static_cast<int>((*(op.kickers.begin() + i)).value)) {
        return 1;
      } else if (static_cast<int>((*(hero.kickers.begin() + i)).value) <
                 static_cast<int>((*(op.kickers.begin() + i)).value)) {
        return 0;
      }
    }
    return 0.5;
  }
}
double valueOrganizer::compairKickers(finalHand &const hero,
                                      finalHand &const op) {
  for (int i = 0; i < 5; i++) {
    if (static_cast<int>((*(hero.kickers.begin() + i)).value) >
        static_cast<int>((*(op.kickers.begin() + i)).value)) {
      return 1;
    } else if (static_cast<int>((*(hero.kickers.begin() + i)).value) <
               static_cast<int>((*(op.kickers.begin() + i)).value)) {
      return 0;
    }
  }
  return 0.5;
}
double valueOrganizer::CompareHands(vector<Card> heroHand, vector<Card> opHand,
                                    vector<Card> board) {
  if (heroHand.size() != 2 || opHand.size() != 2 || board.size() != 5) {
    throw "Wrong input data in compare hands!";
  }

  // organizing hand strenght
  finalHand hero = org.calcHandStrenght(heroHand, board);
  finalHand op = org.calcHandStrenght(opHand, board);
  if (hero.strenght > op.strenght) {
    return 1;
  } else if (hero.strenght < op.strenght) {
    return 0;
  } else {
    switch (hero.strenght) {
      // strFlush
    case 9:
      return this->compairStrFlushes(hero, op);
      break;

      // 4 of a kind
    case 8:
      return this->compair4OfAKinds(hero, op);
      break;

      // full house
    case 7:
      return this->compairFullHouses(hero, op);
      break;

      // flush
    case 6:
      return this->compairFlushes(hero, op);
      break;

      // str
    case 5:
      return this->compairStraigts(hero, op);
      break;

      // 3 of a kind
    case 4:
      return this->compair3OfAKinds(hero, op);
      break;

      // 2 pairs
    case 3:
      return this->compair2Pairs(hero, op);
      break;

      // pair
    case 2:
      return this->compairPairs(hero, op);
      break;

      // kicker
    case 1:
      return this->compairKickers(hero, op);
      break;

    default:
      throw "Unknown strenght of hand";
      break;
    }
  }
}
// TODO :
// add posibility to use XYo, XYs - offsuites and suites instead of all
// returns percentage of hero win probability 0-100%
double valueOrganizer::compareHandVSRange(string heroHand, string opRange,
                                          string board) {
  vector<Card> hero;
  vector<Card> op;
  vector<Card> boardCards;
  vector<Card> deck = fillDeck();
  double heroWins = 0;
  double draws = 0;
  int handsDilt = 0;
  vector<string> heroHandStr = split(heroHand);
  hero.push_back(Card(*(heroHandStr.begin())));
  hero.push_back(Card(*(heroHandStr.begin() + 1)));
  vector<string> boardVec = split(board);
  for (auto i = boardVec.begin(); i != boardVec.end(); i++) {
    boardCards.push_back(Card(*i));
  }

  deck = cutDeck(deck, boardCards);
  deck = cutDeck(deck, hero);
  vector<string> opHands = split(opRange);
  double result = 0;
  for (auto i = opHands.begin(); i != opHands.end(); i++) {
    op.push_back(Card(i->substr(0, 2)));
    op.push_back(Card(i->substr(2, 2)));
    deck = cutDeck(deck, op);
    switch (boardCards.size()) {
    case 0:
      throw std::invalid_argument("TODO handle this with preculced results");
      break;
    case 3:

      for (auto j = deck.begin(); j != deck.end(); j++) {
        for (auto k = j + 1; k != deck.end(); k++) {
          boardCards.push_back(*j);
          boardCards.push_back(*k);
          result = CompareHands(hero, op, boardCards);
          heroWins += result;
          if (result == 0.5) {
            draws++;
          }
          handsDilt++;
          boardCards.erase(boardCards.end() - 1);
          boardCards.erase(boardCards.end() - 2);
        }
      }
      break;
    case 4:
      for (auto j = deck.begin(); j != deck.end(); j++) {
        boardCards.push_back(*j);
        result = CompareHands(hero, op, boardCards);
        heroWins += result;
        if (result == 0.5) {
          draws++;
        }
        handsDilt++;
        boardCards.erase(boardCards.end() - 1);
      }
      break;
    case 5:
      result = CompareHands(hero, op, boardCards);
      heroWins += result;
      if (result == 0.5) {
        draws++;
      }
      handsDilt++;
      break;
    default:
      break;
    }
    op.pop_back();
    op.pop_back();
    deck.push_back(Card(i->substr(0, 2)));
    deck.push_back(Card(i->substr(2, 2)));
  }
  // heroWins*100/handsDilt --- win
  // heroWins-(draws*0.5) - win probality
  // draws --- draw
  //
  return heroWins * 100 / handsDilt;
}