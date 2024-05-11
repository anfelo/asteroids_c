#ifndef DEBUG_H_
#define DEBUG_H_

#include "vendors/raylib/raylib.h"

/// @brief Call from within a BeginDrawing2D
void ShowDebugMenu(void);

/// @brief Call from within a BeginDrawing2D
void ShowDebugVisualizations(int asteroidCount, int projectileCount);

void SetLastCone(Vector2 position, Vector2 velocity);
void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation);

#endif
