
#pragma once

#include <AzCore/EBus/EBus.h>
#include <Deck\DeckFramework.h>

namespace Solitaire
{
    class SolitaireRequests
        : public AZ::EBusTraits,
          public IDeckFramework
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////

        virtual AZStd::vector<Card> GetDeck() = 0;
        virtual Card GetCardAtPosition(int position) = 0;
        virtual Card GetCardAtCurrentPosition() = 0;
        virtual Card GetNextCard() = 0;
        virtual void ResetDeckPosition() = 0;
        virtual void ShuffleDeck() = 0;
    };
    using SolitaireRequestBus = AZ::EBus<SolitaireRequests>;
} // namespace Solitaire
