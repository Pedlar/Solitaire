#pragma once
#include "AzCore\Component\Component.h"
#include "AzCore\EBus\EBus.h"
#include "Card\CardModel.h"

namespace Solitaire {
    class CardSpawnerRequests
        : public AZ::EBusTraits {
    public:
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
        static const bool EnableEventQueue = true;

        typedef AZ::EntityId BusIdType;

        virtual void SpawnCard(Card card) = 0;
    };

    using CardSpawnerRequestBus = AZ::EBus<CardSpawnerRequests>;
}