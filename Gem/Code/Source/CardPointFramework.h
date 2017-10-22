#pragma once
#include <AzCore\std\containers\vector.h>
#include <Card\CardModel.h>
#include "AzCore\EBus\EBus.h"

namespace Solitaire {
    class CardPointFramework {
    public:
        AZ_TYPE_INFO(CardPointFramework, "{ff7afd26-b540-11e7-abc4-cec278b6b50a}");
        CardPointFramework();
        ~CardPointFramework();

        AZStd::vector<Card> GetCardPoints();
    private:
        AZStd::vector<CardPoint> CardPoints;
    };
}