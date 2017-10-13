#pragma once
#include <AzCore\std\containers\map.h>
#include "AzCore\Component\Component.h"
#include <AzFramework/Entity/EntityContextBus.h>
#include <AzCore\Slice\SliceAsset.h>

#include "Solitaire\CardSpawnerBus.h"

namespace Solitaire {
    class CardSpawnerComponent
        : public AZ::Component,
          public CardSpawnerRequestBus::Handler,
          private AzFramework::SliceInstantiationResultBus::MultiHandler {
    public:
        AZ_COMPONENT(CardSpawnerComponent, "{689c426a-ab50-11e7-abc4-cec278b6b50a}")
        CardSpawnerComponent();
        ~CardSpawnerComponent() override {};

        static void Reflect(AZ::ReflectContext* reflection);

        void Init() override;
        void Activate() override;
        void Deactivate() override;

        void SpawnCard(const Card& card) override;

        // SliceInstantiationResultBus::MultiHandler
        void OnSlicePreInstantiate(const AZ::Data::AssetId& sliceAssetId, const AZ::SliceComponent::SliceInstanceAddress& sliceAddress) override;
        void OnSliceInstantiated(const AZ::Data::AssetId& sliceAssetId, const AZ::SliceComponent::SliceInstanceAddress& sliceAddress) override;
        void OnSliceInstantiationFailed(const AZ::Data::AssetId& sliceAssetId) override;
    private:
        
        AZ::Data::Asset<AZ::DynamicSliceAsset> sliceAsset;
        AZStd::map<AzFramework::SliceInstantiationTicket, Card, AZStd::less<AzFramework::SliceInstantiationTicket>, AZStd::allocator> ticketCardMap = AZStd::map<AzFramework::SliceInstantiationTicket, Card, AZStd::less<AzFramework::SliceInstantiationTicket>, AZStd::allocator>();
    
        void SetSubMtlOfCard(const AZ::SliceComponent::EntityList & entites, Card card);
        void SetSubMtlOfEntityForCard(AZ::Entity *, Card card);
        int GetMtlPosition(Card card);
        AZ::Transform GetSpawnTransform();
    };
}