#include "StdAfx.h"
#include "CardModel.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore\RTTI\BehaviorContext.h>

namespace Solitaire {
    CardType::Suit Card::GetSuit() const {
        return cardSuit;
    }

    int Card::GetValue() const {
        return value;
    }
}
