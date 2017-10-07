#include "StdAfx.h"

#include <IRenderer.h>
#include <IGameFramework.h>

#include "MouseInputComponent.h"
#include "AzCore\Serialization\EditContext.h"
#include "AzCore\Math\Transform.h"
#include "AzCore\Component\TransformBus.h"

#include "MathConversion.h"

#include "AzFramework\Input\Devices\Mouse\InputDeviceMouse.h"

#include "LmbrCentral\Physics\PhysicsSystemComponentBus.h"

#include "Solitaire\MouseHitEventBus.h"

using namespace Solitaire;

void MouseInputComponent::Reflect(AZ::ReflectContext* reflection) {
    if (auto serializationContext = azrtti_cast<AZ::SerializeContext*>(reflection)) {
        serializationContext->Class<MouseInputComponent>()
            ->Version(1);

        if (auto editContext = serializationContext->GetEditContext()) {
            editContext->Class<MouseInputComponent>("MouseInputComponent", "Mouse Input Handler Component")
                ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                ->Attribute(AZ::Edit::Attributes::Category, "Solitaire")
                ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game"));
        }
    }
}

void MouseInputComponent::Init() {

}

void MouseInputComponent::Activate() {
    AZ::TickBus::Handler::BusConnect();
    AZ::RenderNotificationsBus::Handler::BusConnect();
    AzFramework::InputChannelEventListener::Connect();
}

void MouseInputComponent::Deactivate() {
    AZ::TickBus::Handler::BusDisconnect();
    AZ::RenderNotificationsBus::Handler::BusDisconnect();
    AzFramework::InputChannelEventListener::Disconnect();
}

void MouseInputComponent::OnScene3DEnd() {
    if (ShouldCheckRayCastHit) {
        ShouldCheckRayCastHit = false;
        PerformRayCastCheck();
    }
}

void MouseInputComponent::OnTick(float deltaTime, AZ::ScriptTimePoint time) {
    MouseHitEvents::ExecuteQueuedEvents();
}

bool MouseInputComponent::OnInputChannelEventFiltered(const AzFramework::InputChannel& inputChannel) {
    AzFramework::InputDeviceId deviceId = inputChannel.GetInputDevice().GetInputDeviceId();

    if (deviceId == AzFramework::InputDeviceMouse::Id) {
        if (inputChannel.GetInputChannelId() == AzFramework::InputDeviceMouse::Button::Left) {
            AzFramework::InputChannel::State buttonState = inputChannel.GetState();
            switch (buttonState) {
            case AzFramework::InputChannel::State::Began:
                const AzFramework::InputChannel::PositionData2D* positionData = inputChannel.GetCustomData<AzFramework::InputChannel::PositionData2D>();

                AZ::Vector2 mouseVector2 = positionData->m_normalizedPosition;

                float xMouse = mouseVector2.GetX() * gEnv->pRenderer->GetWidth();
                float yMouse = mouseVector2.GetY() * gEnv->pRenderer->GetHeight();

                float invMouseY = static_cast<float>(gEnv->pRenderer->GetHeight()) - yMouse;

                LastClickedMousePosition = AZ::Vector2{ xMouse, invMouseY };
                ShouldCheckRayCastHit = true;
                break;
            }
        }
    }

    return false;
}

void MouseInputComponent::PerformRayCastCheck() {
    float xMouse = LastClickedMousePosition.GetX();
    float invMouseY = LastClickedMousePosition.GetY();

    Vec3 vPos0(0, 0, 0);
    gEnv->pRenderer->UnProjectFromScreen(xMouse, invMouseY, 0, &vPos0.x, &vPos0.y, &vPos0.z);

    Vec3 vPos1(0, 0, 0);
    gEnv->pRenderer->UnProjectFromScreen(xMouse, invMouseY, 1, &vPos1.x, &vPos1.y, &vPos1.z);

    Vec3 vDir = vPos1 - vPos0;
    vDir.Normalize();

    float maxDistance = 100.f;

    CryLogAlways("Position{%f,%f,%f}", vPos0.x, vPos0.y, vPos0.z);

    LmbrCentral::PhysicsSystemRequests::RayCastConfiguration config;
    config.m_origin = LYVec3ToAZVec3(vPos0);
    config.m_direction = LYVec3ToAZVec3(vDir);
    config.m_maxHits = 1;
    config.m_maxDistance = maxDistance;
    config.m_physicalEntityTypes = LmbrCentral::PhysicalEntityTypes::Living 
        | LmbrCentral::PhysicalEntityTypes::Dynamic 
        | LmbrCentral::PhysicalEntityTypes::Independent
        | LmbrCentral::PhysicalEntityTypes::Static;

    LmbrCentral::PhysicsSystemRequests::RayCastResult result;
    EBUS_EVENT_RESULT(result, LmbrCentral::PhysicsSystemRequestBus, RayCast, config);

    if (result.GetHitCount() > 0) {
        auto hit = result.GetHit(0);
        if (hit->IsValid()) {
            EBUS_QUEUE_EVENT_ID(hit->m_entityId, MouseHitEvents, OnMouseHit);
        }
    }

    if (auto *pPersistentDebug = gEnv->pGame->GetIGameFramework()->GetIPersistentDebug()) {
        const ColorF green(0.000f, 1.000f, 0.000f);
        const ColorF red(1.000f, 0.000f, 0.000f);

        pPersistentDebug->Begin("FG_Line", true);

        auto end = vPos0 + (vDir *  maxDistance);

        if (result.GetHitCount() > 0) {
            pPersistentDebug->AddLine(vPos0, end, green, 500);
        }
        else {
            pPersistentDebug->AddLine(vPos0, end, red, 500);
        }
    }
}