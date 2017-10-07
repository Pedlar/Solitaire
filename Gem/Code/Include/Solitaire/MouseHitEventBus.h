#pragma once
#include "AzCore\Component\Component.h"
#include "AzCore\EBus\EBus.h"

namespace Solitaire {
    class MouseHitEventBus
        : public AZ::EBusTraits {
    public:
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
        static const bool EnableEventQueue = true;
        
        typedef AZ::EntityId BusIdType;

        virtual void OnMouseHit() = 0;
    };

    using MouseHitEvents = AZ::EBus<MouseHitEventBus>;
}