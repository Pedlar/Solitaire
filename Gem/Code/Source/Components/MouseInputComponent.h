#pragma once
#include "AzCore\Component\Component.h"
#include "AzFramework\Input\Events\InputChannelEventListener.h"
#include <AzFramework\Input\Channels\InputChannel.h>
#include <AzCore\Component\TickBus.h>

#include <RenderBus.h>

namespace Solitaire {
    class MouseInputComponent
        : public AZ::Component,
          public AzFramework::InputChannelEventListener,
          public AZ::TickBus::Handler,
          public AZ::RenderNotificationsBus::Handler {
    public:
        AZ_COMPONENT(MouseInputComponent, "{75508794-aafd-11e7-abc4-cec278b6b50a}")

        ~MouseInputComponent() override {};

        static void Reflect(AZ::ReflectContext* reflection);

        virtual int GetTickOrder() override {
            return AZ::ComponentTickBus::TICK_PHYSICS;
        };

        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void OnTick(float deltaTime, AZ::ScriptTimePoint time);
        bool OnInputChannelEventFiltered(const AzFramework::InputChannel& inputChannel);

        // We need to do our Mouse Unprojecting in the Render Thread, this is the only emitter I could find currently
        void OnScene3DEnd();
    private:
        bool ShouldCheckRayCastHit = false;
        AZ::Vector2 LastClickedMousePosition = AZ::Vector2::CreateZero();
        AZ::EntityId LastHitEntityId;

        void PerformRayCastCheck();
    };
}