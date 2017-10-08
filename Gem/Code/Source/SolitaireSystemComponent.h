
#pragma once

#include <AzCore/Component/Component.h>

#include <Solitaire/SolitaireBus.h>

namespace Solitaire
{
    class SolitaireSystemComponent
        : public AZ::Component
        , protected SolitaireRequestBus::Handler
    {
    public:
        AZ_COMPONENT(SolitaireSystemComponent, "{EE745DDB-C574-4A04-9C5E-CA2FFBE770A4}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        AZStd::vector<Card> GetDeck();
        Card GetCardAtPosition(int position);
        Card GetCardAtCurrentPosition();
        Card GetNextCard();
        void ResetDeckPosition();
        void ShuffleDeck();
    protected:
        ////////////////////////////////////////////////////////////////////////
        // SolitaireRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////


    private:
        DeckFramework mDeckFramework;
    };
}
