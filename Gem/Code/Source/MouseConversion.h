#pragma once

#include <IRenderer.h>
#include <IGameFramework.h>

#include <AzCore\Math\Vector2.h>

inline AZ::Vector2 AZMousePositionToLYMousePosition(AZ::Vector2 vector2) {
    return AZ::Vector2(vector2.GetX() * gEnv->pRenderer->GetWidth(), vector2.GetY() * gEnv->pRenderer->GetHeight());
}