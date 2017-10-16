#include "StdAfx.h"
#include "CardComponent.h"
#include "AzCore\Serialization\EditContext.h"
#include "AzCore\Math\Transform.h"
#include "AzCore\Component\TransformBus.h"

using namespace Solitaire;

void CardComponent::Reflect(AZ::ReflectContext* reflection) {
    if (auto serializationContext = azrtti_cast<AZ::SerializeContext*>(reflection)) {
        serializationContext->Class<CardComponent>()
            ->Version(1);

        if (auto editContext = serializationContext->GetEditContext()) {
            editContext->Class<CardComponent>("CardComponent", "The Component for the Card")
                ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                ->Attribute(AZ::Edit::Attributes::Category, "Solitaire")
                ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"));
        }
    }
}

void CardComponent::Init() {

}

void CardComponent::Activate() {
    AZ::TickBus::Handler::BusConnect();
    MouseHitEventsBus::Handler::BusConnect(GetEntityId());
}

void CardComponent::Deactivate() {
    MouseHitEventsBus::Handler::BusDisconnect();
    AZ::TickBus::Handler::BusDisconnect();
}

void CardComponent::OnTick(float deltaTime, AZ::ScriptTimePoint time) {
    AZ::Vector3 newPosition = AZ::Vector3::CreateZero();

    AZ::Transform transform = AZ::Transform::Identity();
    EBUS_EVENT_ID_RESULT(transform, GetEntityId(), AZ::TransformBus, GetWorldTM);

    if (!lastMousePosition.IsZero()) {
        if (transform != AZ::Transform::Identity()) {
            AZ::Vector3 newPosition = transform.GetPosition().Lerp(lastMousePosition + AZ::Vector3(0.f, 0.f, .5f), 2.f);
        }
    }

    if (!newPosition.IsZero()) {
        transform.SetPosition(newPosition);
        EBUS_EVENT_ID(GetEntityId(), AZ::TransformBus, SetWorldTM, transform);
    }
}

void CardComponent::OnMouseHit(MouseHitEvents::MouseData mouseData) {

}


void CardComponent::OnMouseHeld(MouseHitEvents::MouseData mouseData) {
    TrackMouseMovement(mouseData.GetLastPosition());
}

void CardComponent::OnMouseEnd(MouseHitEvents::MouseData mouseData) {
    lastMousePosition = AZ::Vector3::CreateZero();
}

void CardComponent::TrackMouseMovement(AZ::Vector3 position) {
    lastMousePosition = position;
}