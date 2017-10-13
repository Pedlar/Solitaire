#pragma once
#include "AzCore\Component\Component.h"
#include "AzCore\RTTI\TypeInfo.h"

#include "Solitaire\Card\CardTypes.h"

namespace Solitaire {

    class Card {
    public:
        AZ_TYPE_INFO(Card, "{689c4652-ab50-11e7-abc4-cec278b6b50a}");
        Card(CardType::Suit suit, int value) :
            value(value),
            cardSuit(suit) { }

        Card() = default;
        ~Card() = default;

        CardType::Suit GetSuit() const;
        int GetValue() const;

        int value;
        CardType::Suit cardSuit;

        inline string ToString() {
            return "Card{" + CardType::ToString(cardSuit) + "," + value + "}";
        }
    };
}