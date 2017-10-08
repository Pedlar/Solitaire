#pragma once
#include "IDeckFramework.h"
#include "AzCore\EBus\EBus.h"

namespace Solitaire {
    class DeckFramework : 
        public IDeckFramework {
    public:
        AZ_TYPE_INFO(DeckFramework, "{0d78e888-abba-11e7-abc4-cec278b6b50a}");
        DeckFramework();
        ~DeckFramework();

        /* IDeckFramework */
        AZStd::vector<Card> GetDeck() override;
        Card GetCardAtPosition(int position) override;
        Card GetCardAtCurrentPosition() override;
        Card GetNextCard() override;
        void ResetDeckPosition() override;
        void ShuffleDeck() override;

    private:
        AZStd::vector<Card> CardList;
        int CurrentCardPosition;
    };
}