#include "StdAfx.h"
#include "CardComponent.h"
#include "AzCore\Serialization\EditContext.h"
#include "AzCore\Math\Transform.h"
#include "AzCore\Component\TransformBus.h"
#include "LmbrCentral\Shape\ShapeComponentBus.h"
#include "LmbrCentral\Physics\PhysicsSystemComponentBus.h"

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

    cardAabb = AZ::Aabb::CreateNull();
    EBUS_EVENT_ID_RESULT(cardAabb, GetEntityId(), LmbrCentral::ShapeComponentRequestsBus, GetEncompassingAabb);
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
        newPosition = lastMousePosition;//transform.GetPosition().Lerp(lastMousePosition + AZ::Vector3(0.f, 0.f, .5f), 2.f);
    }

    if (!travelToPosition.IsZero()) {
        newPosition = transform.GetPosition().Lerp(travelToPosition, .05f);

        // Only check X and Y because Z is calculated for us
        if (newPosition.GetX() == transform.GetPosition().GetX()
            && newPosition.GetY() == transform.GetPosition().GetY()) {
            newPosition = AZ::Vector3::CreateZero();
            travelToPosition = AZ::Vector3::CreateZero();
        }
    }

    if(!newPosition.IsZero()) {
        AZStd::vector<AZ::EntityId> entities;
        EBUS_EVENT_RESULT(entities, LmbrCentral::PhysicsSystemRequestBus, GatherPhysicalEntitiesInAABB, cardAabb, LmbrCentral::PhysicalEntityTypes::All);

        AZ::VectorFloat maxHeight = 0.f;

        for each (AZ::EntityId entityId in entities) {
            if (entityId == GetEntityId())
                continue;

            AZ::Transform transform = AZ::Transform::Identity();
            EBUS_EVENT_ID_RESULT(transform, entityId, AZ::TransformBus, GetWorldTM);
            if (transform.GetPosition().GetZ() > maxHeight) {
                maxHeight = transform.GetPosition().GetZ();
            }
        }

        if (maxHeight > 0) {
            newPosition.SetZ(maxHeight + .5f);
        }

        if (!newPosition.IsZero()) {
            transform.SetPosition(newPosition);
            EBUS_EVENT_ID(GetEntityId(), AZ::TransformBus, SetWorldTM, transform);
        }
    }
}

void CardComponent::OnMouseHit(MouseHitEvents::MouseData mouseData) {
    travelToPosition = AZ::Vector3::CreateZero();
}


void CardComponent::OnMouseHeld(MouseHitEvents::MouseData mouseData) {
    TrackMouseMovement(mouseData.GetLastPosition());
}

void CardComponent::OnMouseEnd(MouseHitEvents::MouseData mouseData) {
    lastMousePosition = AZ::Vector3::CreateZero();

    AZStd::vector<AZ::EntityId> entities;
    EBUS_EVENT_RESULT(entities, LmbrCentral::PhysicsSystemRequestBus, GatherPhysicalEntitiesInAABB, cardAabb, LmbrCentral::PhysicalEntityTypes::All);

    AZ::VectorFloat maxHeight = 0.f;

    for each (AZ::EntityId entityId in entities) {
        if (entityId == GetEntityId())
            continue;
        
        // TODO: Check if touching a card
    }

    travelToPosition = AZ::Vector3(101.f, 83.f, 32.1f);
}

void CardComponent::TrackMouseMovement(AZ::Vector3 position) {
    lastMousePosition = position;
}