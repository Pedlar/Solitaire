#pragma once
#include "AzCore\Component\Component.h"
#include "Solitaire\CardSpawnerBus.h"

namespace Solitaire {
    class CardSpawnerComponent
        : public AZ::Component,
          public CardSpawnerRequestBus::Handler {
    public:
        AZ_COMPONENT(CardSpawnerComponent, "{  }")

        ~CardSpawnerComponent() override {};

        static void Reflect(AZ::ReflectContext* reflection);

        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void SpawnCard(int cardValue) override;
    };
}