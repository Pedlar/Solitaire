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
    MouseHitEventsBus::Handler::BusConnect(GetEntityId());
}

void CardComponent::Deactivate() {
    MouseHitEventsBus::Handler::BusDisconnect();
}

void CardComponent::OnMouseHit(MouseHitEvents::MouseData mouseData) {
    CryLogAlways("OnMouseHit: %f %f", mouseData.GetPosition().GetX(), mouseData.GetPosition().GetY());
}


void CardComponent::OnMouseHeld(MouseHitEvents::MouseData mouseData) {
    CryLogAlways("OnMouseHeld: %f %f", mouseData.GetPosition().GetX(), mouseData.GetPosition().GetY());

}

void CardComponent::OnMouseEnd(MouseHitEvents::MouseData mouseData) {
    CryLogAlways("OnMouseEnd: %f %f", mouseData.GetPosition().GetX(), mouseData.GetPosition().GetY());

}