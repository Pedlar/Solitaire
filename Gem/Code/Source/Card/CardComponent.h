#pragma once
#include "AzCore\Component\Component.h"
#include "Solitaire\MouseHitEventBus.h"


namespace Solitaire {
    class CardComponent
        : public AZ::Component,
          public MouseHitEventsBus::Handler {
    public:
        AZ_COMPONENT(CardComponent, "{af8cc084-b0fd-11e7-abc4-cec278b6b50a}")

        ~CardComponent() override {};

        static void Reflect(AZ::ReflectContext* reflection);

        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void OnMouseHit(MouseHitEvents::MouseData mouseData);
        void OnMouseHeld(MouseHitEvents::MouseData mouseData);
        void OnMouseEnd(MouseHitEvents::MouseData mouseData);
    };
}