#include "StdAfx.h"
#include <IRenderer.h>
#include <IGameFramework.h>
#include <MathConversion.h>
#include "CardSpawnerComponent.h"
#include "AzCore\Serialization\EditContext.h"
#include "AzCore\Math\Transform.h"
#include "AzCore\Component\TransformBus.h"
#include <AzCore\RTTI\BehaviorContext.h>
#include <AzFramework\Entity\GameEntityContextBus.h>
#include <LmbrCentral\Rendering\MeshComponentBus.h>
#include <LmbrCentral\Rendering\MaterialOwnerBus.h>
#include <AzCore\Asset\AssetManagerBus.h>
#include <LmbrCentral\Physics\PhysicsSystemComponentBus.h>
#include "Solitaire\CardComponentRequestBus.h"

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

void CardSpawnerComponent::SpawnCard(const Card& card) {
    
    AZ::Transform transform = GetSpawnTransform();

    AzFramework::SliceInstantiationTicket ticket;
    EBUS_EVENT_RESULT(ticket, AzFramework::GameEntityContextRequestBus, InstantiateDynamicSlice, sliceAsset, transform, nullptr);

    ticketCardMap[ticket] = card;

    CryLogAlways("Card: %s %d", CardType::ToString(ticketCardMap[ticket].GetSuit()), ticketCardMap[ticket].GetValue());

    AzFramework::SliceInstantiationResultBus::MultiHandler::BusConnect(ticket);
}

void CardSpawnerComponent::OnSlicePreInstantiate(const AZ::Data::AssetId& sliceAssetId, const AZ::SliceComponent::SliceInstanceAddress& sliceAddress) {

}

void CardSpawnerComponent::OnSliceInstantiated(const AZ::Data::AssetId& sliceAssetId, const AZ::SliceComponent::SliceInstanceAddress& sliceAddress) {
    const AzFramework::SliceInstantiationTicket& ticket = (*AzFramework::SliceInstantiationResultBus::GetCurrentBusId());
    Card card = ticketCardMap[ticket];

    AzFramework::SliceInstantiationResultBus::MultiHandler::BusDisconnect(ticket);

    SetSubMtlOfCard(sliceAddress.second->GetInstantiated()->m_entities, card);
    //SetMeshOnSliceEntity(sliceAddress.second->GetInstantiated()->m_entities);
}

void CardSpawnerComponent::OnSliceInstantiationFailed(const AZ::Data::AssetId& sliceAssetId) {
    
}

void CardSpawnerComponent::SetSubMtlOfCard(const AZ::SliceComponent::EntityList& entities, Card card) {
    //const AZ::SliceComponent::EntityList& entities = sliceAddress.second->GetInstantiated()->m_entities
    AZStd::vector<AZ::EntityId> entityIds;
    entityIds.reserve(entities.size());
    for (AZ::Entity* currEntity : entities) {
        if ("CardModel" == currEntity->GetName()) {
            CryLogAlways("CardModel Entity!");
            SetSubMtlOfEntityForCard(currEntity, card);
            SetCardOnCardComponent(currEntity, card);
        }
    }
}

void CardSpawnerComponent::SetCardOnCardComponent(AZ::Entity* entity, Card card) {
    AZ::EntityId entityId = entity->GetId();

    EBUS_EVENT_ID(entityId, CardComponenetRequesttBus, SetCard, card);
}

void CardSpawnerComponent::SetSubMtlOfEntityForCard(AZ::Entity* entity, Card card) {
    AZ::EntityId entitiyId = entity->GetId();

    _smart_ptr<IMaterial> material;
    EBUS_EVENT_ID_RESULT(material, entitiyId, LmbrCentral::MaterialOwnerRequestBus, GetMaterial);
    if (material) {
        CryLogAlways("Have Material Position: %d", GetMtlPosition(card));
        _smart_ptr<IMaterial> subMaterial = material->GetSafeSubMtl(GetMtlPosition(card));
        if (subMaterial) {
            CryLogAlways("Have Sub Material");
            EBUS_EVENT_ID(entitiyId, LmbrCentral::MaterialOwnerRequestBus, SetMaterial, subMaterial);
        }
    }
}

int CardSpawnerComponent::GetMtlPosition(Card card) {
    int modifier = 0;
    switch (card.GetSuit()) {
    case CardType::Suit::CLUB:
        modifier = 0;
        break;
    case CardType::Suit::DIAMOND:
        modifier = 1 * 13;
        break;
    case CardType::Suit::HEART:
        modifier = 2 * 13;
        break;
    case CardType::Suit::SPADE:
        modifier = 3 * 13;
        break;
    }

    CryLogAlways("Card: %s %d", CardType::ToString(card.GetSuit()), card.GetValue());
    CryLogAlways("Math: (%d + %d) = %d", card.GetValue(), modifier, card.GetValue() + modifier);

    return card.GetValue() + modifier;
}

AZ::Transform CardSpawnerComponent::GetSpawnTransform() {
    AZ::Transform transform = AZ::Transform::Identity();
    EBUS_EVENT_ID_RESULT(transform, GetEntityId(), AZ::TransformBus, GetWorldTM);

    AZ::Vector3 origin = transform.GetPosition() + AZ::Vector3(.0f, .0f, 10.f);
    AZ::Vector3 direction = (AZ::Vector3(origin.GetX(), origin.GetY(), 0.0f) - origin);
    direction.Normalize();

    LmbrCentral::PhysicsSystemRequests::RayCastConfiguration config = LmbrCentral::PhysicsSystemRequests::RayCastConfiguration();
    config.m_direction = direction;
    config.m_maxDistance = 20.0f;
    config.m_maxHits = 1;
    config.m_origin = origin;

    LmbrCentral::PhysicsSystemRequests::RayCastResult rayResult;
    EBUS_EVENT_RESULT(rayResult, LmbrCentral::PhysicsSystemRequestBus, RayCast, config);

    if (rayResult.GetHitCount() > 0) {
        auto hit = rayResult.GetHit(0);
        if (hit->IsValid()) {
            transform.SetTranslation(hit->m_position + AZ::Vector3(.0f, .0f, 0.05f));
        }
    }

    if (auto *pPersistentDebug = gEnv->pGame->GetIGameFramework()->GetIPersistentDebug()) {
        const ColorF green(0.000f, 1.000f, 0.000f);
        const ColorF red(1.000f, 0.000f, 0.000f);

        pPersistentDebug->Begin("FG_Line", true);

        auto end = origin + (direction *  20.0f);

        if (rayResult.GetHitCount() > 0) {
            pPersistentDebug->AddLine(AZVec3ToLYVec3(origin), AZVec3ToLYVec3(end), green, 500);
        }
        else {
            pPersistentDebug->AddLine(AZVec3ToLYVec3(origin), AZVec3ToLYVec3(end), red, 500);
        }
    }

    return transform;
}

/*
void CardSpawnerComponent::SetMeshOnEntity(AZ::Entity* entity) {
    AZ::Data::AssetId meshAssetId;
    const string meshName = "objects/card_model.cgf";
    EBUS_EVENT_RESULT(meshAssetId, AZ::Data::AssetCatalogRequestBus, GetAssetIdByPath, meshName, AZ::AzTypeInfo<AZ::Data::AssetData>::Uuid(), true);
    if (meshAssetId.IsValid()) {
        EBUS_EVENT_ID(entity->GetId(), LmbrCentral::MeshComponentRequestBus, SetMeshAsset, meshAssetId);
    }
}
*/