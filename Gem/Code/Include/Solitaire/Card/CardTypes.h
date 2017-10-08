#pragma once

struct CardType {
    enum Suit {
        CLUB,
        DIAMOND,
        HEART,
        SPADE
    };

    static string ToString(const Suit enumValue) {
        switch (enumValue) {
        case CLUB:
            return "CLUB";
        case DIAMOND:
            return "DIAMOND";
        case HEART:
            return "HEART";
        case SPADE:
            return "SPADE";
        default:
            return "UNKNOWN";
        }
    }
};