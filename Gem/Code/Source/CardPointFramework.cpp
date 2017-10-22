#include "StdAfx.h"
#include "CardPointFramework.h"

namespace Solitaire {
    CardPointFramework::CardPointFramework() {
        CardList = AZStd::initializer_list<Card>();
    }

    CardPointFramework::~CardPointFramework() {
        CardList.clear();
    }

    AZStd::vector<Card> GetCardsOnCardPoint() {

    }

    Card GetCardAtPosition(int position) {

    }

    Card GetCardAtTop() {

    }
}
