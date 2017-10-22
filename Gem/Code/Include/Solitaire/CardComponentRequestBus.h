#pragma once
#include "AzCore\Component\Component.h"
#include "AzCore\EBus\EBus.h"
#include "Card\CardModel.h"

namespace Solitaire {
    class CardComponenetRequests
        : public AZ::EBusTraits {
    public:
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
        static const bool EnableEventQueue = true;

        typedef AZ::EntityId BusIdType;

        virtual void SetCard(const Card card) = 0;
        virtual Card GetCard() = 0;
    };

    using CardComponenetRequesttBus = AZ::EBus<CardComponenetRequests>;
}