#include "StdAfx.h"
#include "DeckFramework.h"

namespace Solitaire {
    DeckFramework::DeckFramework() {
        CardList = AZStd::initializer_list<Card>({
            Card(CardType::Suit::CLUB, 0),  Card(CardType::Suit::CLUB, 1),  Card(CardType::Suit::CLUB, 2),
            Card(CardType::Suit::CLUB, 3),  Card(CardType::Suit::CLUB, 4),  Card(CardType::Suit::CLUB, 5),
            Card(CardType::Suit::CLUB, 6),  Card(CardType::Suit::CLUB, 7),  Card(CardType::Suit::CLUB, 8),
            Card(CardType::Suit::CLUB, 9),  Card(CardType::Suit::CLUB, 10), Card(CardType::Suit::CLUB, 11),
            Card(CardType::Suit::CLUB, 12), Card(CardType::Suit::CLUB, 13),

            Card(CardType::Suit::DIAMOND, 0),  Card(CardType::Suit::DIAMOND, 1),  Card(CardType::Suit::DIAMOND, 2),
            Card(CardType::Suit::DIAMOND, 3),  Card(CardType::Suit::DIAMOND, 4),  Card(CardType::Suit::DIAMOND, 5),
            Card(CardType::Suit::DIAMOND, 6),  Card(CardType::Suit::DIAMOND, 7),  Card(CardType::Suit::DIAMOND, 8),
            Card(CardType::Suit::DIAMOND, 9),  Card(CardType::Suit::DIAMOND, 10), Card(CardType::Suit::DIAMOND, 11),
            Card(CardType::Suit::DIAMOND, 12), Card(CardType::Suit::DIAMOND, 13),

            Card(CardType::Suit::HEART, 0),  Card(CardType::Suit::HEART, 1),  Card(CardType::Suit::HEART, 2),
            Card(CardType::Suit::HEART, 3),  Card(CardType::Suit::HEART, 4),  Card(CardType::Suit::HEART, 5),
            Card(CardType::Suit::HEART, 6),  Card(CardType::Suit::HEART, 7),  Card(CardType::Suit::HEART, 8),
            Card(CardType::Suit::HEART, 9),  Card(CardType::Suit::HEART, 10), Card(CardType::Suit::HEART, 11),
            Card(CardType::Suit::HEART, 12), Card(CardType::Suit::HEART, 13),

            Card(CardType::Suit::SPADE, 0),  Card(CardType::Suit::SPADE, 1),  Card(CardType::Suit::SPADE, 2),
            Card(CardType::Suit::SPADE, 3),  Card(CardType::Suit::SPADE, 4),  Card(CardType::Suit::SPADE, 5),
            Card(CardType::Suit::SPADE, 6),  Card(CardType::Suit::SPADE, 7),  Card(CardType::Suit::SPADE, 8),
            Card(CardType::Suit::SPADE, 9),  Card(CardType::Suit::SPADE, 10), Card(CardType::Suit::SPADE, 11),
            Card(CardType::Suit::SPADE, 12), Card(CardType::Suit::SPADE, 13),
        });
    }

    DeckFramework::~DeckFramework() {
        CardList.clear();
    }

    AZStd::vector<Card> DeckFramework::GetDeck() {
        return CardList;
    }

    Card DeckFramework::GetCardAtPosition(int position) {
        return CardList.at(position);
    }

    Card DeckFramework::GetCardAtCurrentPosition() {
        return CardList.at(CurrentCardPosition);
    }

    Card DeckFramework::GetNextCard() {
        Card card = CardList.at(CurrentCardPosition);

        CurrentCardPosition++;
        if (CurrentCardPosition >= CardList.size()) {
            CurrentCardPosition = 0;
            // Todo:: Reset this properly
        }

        return card;
    }

    void DeckFramework::ResetDeckPosition() {
        CurrentCardPosition = 0;
        // TODO: Clean Up Cards that are on the board and not not moved off the deck
    }

    void DeckFramework::ShuffleDeck() {
        // TODO: Shuffle the Vector with a sort
    }
}