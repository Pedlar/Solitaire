#pragma once
#include "AzCore\Component\Component.h"
#include <AzCore\Component\TickBus.h>
#include "Solitaire\MouseHitEventBus.h"
#include "Solitaire\CardComponentRequestBus.h"
#include "LmbrCentral\Physics\PhysicsComponentBus.h"

namespace Solitaire {
    class CardComponent
        : public AZ::Component,
          public AZ::TickBus::Handler,
          public MouseHitEventsBus::Handler,
          public CardComponenetRequesttBus::Handler {
    public:
        AZ_COMPONENT(CardComponent, "{af8cc084-b0fd-11e7-abc4-cec278b6b50a}")

        ~CardComponent() override {};

        static void Reflect(AZ::ReflectContext* reflection);

        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void OnTick(float deltaTime, AZ::ScriptTimePoint time);

        void OnMouseHit(MouseHitEvents::MouseData mouseData);
        void OnMouseHeld(MouseHitEvents::MouseData mouseData);
        void OnMouseEnd(MouseHitEvents::MouseData mouseData);

        inline void SetCard(const Card newCard) { card = newCard; }
        inline Card GetCard() { return card; };
    private:
        void CardComponent::TrackMouseMovement(AZ::Vector3 position);

        AZ::Vector3 lastMousePosition{ 0, 0, 0 };
        AZ::Vector3 mouseChangeAggregate{ 0, 0, 0 };
        AZ::Vector3 travelToPosition{ 0, 0, 0 };

        float MovementSpeed = 5.f;

        AZ::Aabb cardAabb;

        Card card;
    };
}