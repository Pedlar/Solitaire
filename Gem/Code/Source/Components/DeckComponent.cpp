#include "StdAfx.h"
#include "DeckComponent.h"
#include "CardSpawnerComponent.h"
#include "AzCore\Serialization\EditContext.h"
#include "AzCore\Math\Transform.h"
#include "AzCore\Component\TransformBus.h"
#include "Solitaire\SolitaireBus.h"

using namespace Solitaire;

void DeckComponent::Reflect(AZ::ReflectContext* reflection) {
    if (auto serializationContext = azrtti_cast<AZ::SerializeContext*>(reflection)) {
        serializationContext->Class<DeckComponent>()
            ->Field("Spawn Entity", &DeckComponent::SpawnEntityId)
            ->Version(1);

        if (auto editContext = serializationContext->GetEditContext()) {
            editContext->Class<DeckComponent>("DeckComponent", "The Deck Component")
                ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                ->Attribute(AZ::Edit::Attributes::Category, "Solitaire")
                ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"))
                ->DataElement(nullptr, &DeckComponent::SpawnEntityId, "Spawn Entity", "The spawn point for the Entity");
        }
    }
}

void DeckComponent::Init() {

}

void DeckComponent::Activate() {
    if (!SpawnEntityId.IsValid()) {
        SpawnEntityId = GetEntityId();
    }

    MouseHitEvents::Handler::BusConnect(GetEntityId());
}

void DeckComponent::Deactivate() {
    MouseHitEvents::Handler::BusDisconnect();
}

void DeckComponent::OnMouseHit() {

    Card card;
    EBUS_EVENT_RESULT(card, SolitaireRequestBus, GetNextCard);

    CryLogAlways("DeskComponent: I've Been Clicked On!");

    CryLogAlways("Card At Position 2 is: %s %d", CardType::ToString(card.GetSuit()), card.GetValue());

    EBUS_EVENT_ID(SpawnEntityId, CardSpawnerRequestBus, SpawnCard, card);

    AZ::Transform myTransform = AZ::Transform::CreateIdentity();
    EBUS_EVENT_ID_RESULT(myTransform, GetEntityId(), AZ::TransformBus, GetWorldTM);

    CryLogAlways("DeckPosition: %f %f %f", (float)myTransform.GetPosition().GetX(), (float)myTransform.GetPosition().GetY(), (float)myTransform.GetPosition().GetZ());
}