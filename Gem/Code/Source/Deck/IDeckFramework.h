#pragma once
#include <AzCore\std\containers\vector.h>
#include <Card\CardModel.h>

namespace Solitaire {
    class IDeckFramework {
    public:
        /*
            Get the Deck of Cards
        */
        virtual AZStd::vector<Card> GetDeck() = 0;

        /*
            Get Card at Specified location but does not advance;
        */
        virtual Card GetCardAtPosition(int position) = 0;

        /*
            Get Card at Current Deck position but does not advance
        */
        virtual Card GetCardAtCurrentPosition() = 0;

        /*
            Advance the deck position and get the neck Card
        */
        virtual Card GetNextCard() = 0;

        /*
            Reset the deck position to zero. This should be called when reflipping the Deck
        */
        virtual void ResetDeckPosition() = 0;

        /*
            Reset and Shuffle the Deck
        */
        virtual void ShuffleDeck() = 0;
    };
}