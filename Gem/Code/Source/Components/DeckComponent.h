#pragma once
#include "AzCore\Component\Component.h"

#include "Solitaire\MouseHitEventBus.h"

namespace Solitaire {
    class DeckComponent
        : public AZ::Component,
          public MouseHitEventsBus::Handler {
    public:
        AZ_COMPONENT(DeckComponent, "{75508bc2-aafd-11e7-abc4-cec278b6b50a}")

        ~DeckComponent() override {};

        static void Reflect(AZ::ReflectContext* reflection);

        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void OnMouseHit(MouseHitEvents::MouseData mouseData);

        inline void OnMouseHeld(MouseHitEvents::MouseData mouseData) {};
        inline void OnMouseEnd(MouseHitEvents::MouseData mouseData) {};
    private:
        AZ::EntityId SpawnEntityId;
    };
}