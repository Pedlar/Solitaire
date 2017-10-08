
#include "StdAfx.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>

#include "SolitaireSystemComponent.h"
#include <Deck\IDeckFramework.h>
#include "Deck\DeckFramework.h"

namespace Solitaire
{
    void SolitaireSystemComponent::Reflect(AZ::ReflectContext* context) {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context)) {
            serialize->Class<SolitaireSystemComponent, AZ::Component>()
                ->Version(0)
                ->SerializerForEmptyClass();

            if (AZ::EditContext* ec = serialize->GetEditContext()) {
                ec->Class<SolitaireSystemComponent>("Solitaire", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true);
            }
        }
    }

    void SolitaireSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided) {
        provided.push_back(AZ_CRC("SolitaireService"));
    }

    void SolitaireSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible) {
        incompatible.push_back(AZ_CRC("SolitaireService"));
    }

    void SolitaireSystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required) {
        (void)required;
    }

    void SolitaireSystemComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent) {
        (void)dependent;
    }

    void SolitaireSystemComponent::Init() {
        mDeckFramework = DeckFramework();
        CryLogAlways("Starting System Component");
    }

    void SolitaireSystemComponent::Activate() {
        SolitaireRequestBus::Handler::BusConnect();
    }

    void SolitaireSystemComponent::Deactivate() {
        SolitaireRequestBus::Handler::BusDisconnect();
    }

    AZStd::vector<Card> SolitaireSystemComponent::GetDeck() {
        return mDeckFramework.GetDeck();
    }
    
    Card SolitaireSystemComponent::GetCardAtPosition(int position) {
        return mDeckFramework.GetCardAtPosition(position);
    }
    
    Card SolitaireSystemComponent::GetCardAtCurrentPosition() {
        return mDeckFramework.GetCardAtCurrentPosition();
    }
    
    Card SolitaireSystemComponent::GetNextCard() {
        return mDeckFramework.GetNextCard();
    }
    
    void SolitaireSystemComponent::ResetDeckPosition() {
        return mDeckFramework.ResetDeckPosition();
    }

    void SolitaireSystemComponent::ShuffleDeck() {
        return mDeckFramework.ShuffleDeck();
    }
}
