#include "StdAfx.h"
#include "CardSpawnerComponent.h"
#include "AzCore\Serialization\EditContext.h"
#include "AzCore\Math\Transform.h"
#include "AzCore\Component\TransformBus.h"

using namespace Solitaire;

void CardSpawnerComponent::Reflect(AZ::ReflectContext* reflection) {
    if (auto serializationContext = azrtti_cast<AZ::SerializeContext*>(reflection)) {
        serializationContext->Class<CardSpawnerComponent>()
            ->Version(1);

        if (auto editContext = serializationContext->GetEditContext()) {
            editContext->Class<CardSpawnerComponent>("CardSpawnerComponent", "A Spawner to Spawn Cards!")
                ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                ->Attribute(AZ::Edit::Attributes::Category, "Solitaire")
                ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"));
        }
    }
}

void CardSpawnerComponent::Init() {

}

void CardSpawnerComponent::Activate() {

}

void CardSpawnerComponent::Deactivate() {

}

void CardSpawnerComponent::SpawnCard(int cardValue) {

}