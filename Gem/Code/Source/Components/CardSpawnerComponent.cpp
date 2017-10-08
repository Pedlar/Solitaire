#include "StdAfx.h"
#include "CardSpawnerComponent.h"
#include "AzCore\Serialization\EditContext.h"
#include "AzCore\Math\Transform.h"
#include "AzCore\Component\TransformBus.h"
#include <AzCore\RTTI\BehaviorContext.h>
#include <AzFramework\Entity\GameEntityContextBus.h>

using namespace Solitaire;

CardSpawnerComponent::CardSpawnerComponent() {
    sliceAsset.SetFlags(static_cast<AZ::u8>(AZ::Data::AssetFlags::OBJECTSTREAM_NO_LOAD));
}

void CardSpawnerComponent::Reflect(AZ::ReflectContext* reflection) {

    if (auto serializationContext = azrtti_cast<AZ::SerializeContext*>(reflection)) {
        serializationContext->Class<CardSpawnerComponent>()
            ->Field("Slice", &CardSpawnerComponent::sliceAsset)
            ->Version(1);

        if (auto editContext = serializationContext->GetEditContext()) {
            editContext->Class<CardSpawnerComponent>("CardSpawnerComponent", "A Spawner to Spawn Cards!")
                ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                ->Attribute(AZ::Edit::Attributes::Category, "Solitaire")
                ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"))
                ->DataElement(nullptr, &CardSpawnerComponent::sliceAsset, "Dynamic slice", "The slice to spawn");
        }
    }
}

void CardSpawnerComponent::Init() {

}

void CardSpawnerComponent::Activate() {
    CardSpawnerRequestBus::Handler::BusConnect(GetEntityId());
}

void CardSpawnerComponent::Deactivate() {
    CardSpawnerRequestBus::Handler::BusDisconnect();
}

void CardSpawnerComponent::SpawnCard(Card card) {
    AZ::Transform transform = AZ::Transform::Identity();
    EBUS_EVENT_ID_RESULT(transform, GetEntityId(), AZ::TransformBus, GetWorldTM);

    AZ::Transform heightAdjustTransform = AZ::Transform::CreateZero();
    AZ::Vector3 heightAdjustVec = AZ::Vector3{ 0, 0, ticketCardMap.size() * 0.05f };

    transform *= heightAdjustTransform;

    AzFramework::SliceInstantiationTicket ticket;
    EBUS_EVENT_RESULT(ticket, AzFramework::GameEntityContextRequestBus, InstantiateDynamicSlice, sliceAsset, transform, nullptr);

    ticketCardMap.insert(AZStd::pair<AzFramework::SliceInstantiationTicket, Card>(ticket, card));

    AzFramework::SliceInstantiationResultBus::MultiHandler::BusConnect(ticket);
}

void CardSpawnerComponent::OnSlicePreInstantiate(const AZ::Data::AssetId& sliceAssetId, const AZ::SliceComponent::SliceInstanceAddress& sliceAddress) {
    CryLogAlways("Entity Spawned");
}

void CardSpawnerComponent::OnSliceInstantiated(const AZ::Data::AssetId& sliceAssetId, const AZ::SliceComponent::SliceInstanceAddress& sliceAddress) {
    CryLogAlways("Entity Instantiated");
}

void CardSpawnerComponent::OnSliceInstantiationFailed(const AZ::Data::AssetId& sliceAssetId) {
    CryLogAlways("Entity Failed");
}