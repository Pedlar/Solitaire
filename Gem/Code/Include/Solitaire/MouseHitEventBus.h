#pragma once
#include "AzCore\Component\Component.h"
#include <AzCore\Math\Vector2.h>
#include "AzCore\EBus\EBus.h"

namespace Solitaire {
    class MouseHitEvents
        : public AZ::EBusTraits {
    public:
        class MouseData {
        public:
            AZ_TYPE_INFO(MouseData, "{af8cb850-b0fd-11e7-abc4-cec278b6b50a}");
            AZ_CLASS_ALLOCATOR(MouseData, AZ::SystemAllocator, 0);

            MouseData(AZ::Vector2 mousePosition) :
                mousePosition(mousePosition) { };

            inline AZ::Vector2 GetPosition() {
                return mousePosition;
            };

        private:
            AZ::Vector2 mousePosition;
        };

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
        static const bool EnableEventQueue = true;
        
        typedef AZ::EntityId BusIdType;

        virtual void OnMouseHit(MouseData mouseData) = 0;
        virtual void OnMouseHeld(MouseData mouseData) = 0;
        virtual void OnMouseEnd(MouseData mouseData) = 0;
    };

    using MouseHitEventsBus = AZ::EBus<MouseHitEvents>;
}