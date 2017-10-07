
#include "StdAfx.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "SolitaireSystemComponent.h"
#include "Components\DeckComponent.h"
#include "Components\MouseInputComponent.h"
#include "Components\CardSpawnerComponent.h"

#include <IGem.h>

namespace Solitaire
{
    class SolitaireModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(SolitaireModule, "{728158C8-3AFA-4BA3-B051-C423174847EE}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(SolitaireModule, AZ::SystemAllocator, 0);

        SolitaireModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                SolitaireSystemComponent::CreateDescriptor(),
                DeckComponent::CreateDescriptor(),
                MouseInputComponent::CreateDescriptor(),
                CardSpawnerComponent::CreateDescriptor()
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<SolitaireSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(Solitaire_75770ee04b5543aa840cb2687f960c39, Solitaire::SolitaireModule)
