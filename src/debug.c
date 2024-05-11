#include "debug.h"

#include "constants.h"
#include "raygui.h"
#include "vendors/raylib/raylib.h"
#include "vendors/raylib/raymath.h"

static bool _showDebugMenu = false;
static bool _showAngleCone = false;
static bool _showAsteroidCount = false;
static bool _showProjectileCount = false;
static bool _showPlayerInfo = false;

static Vector2 line0[2] = {0};
static Vector2 line1[2] = {0};

static Vector2 _playerPosition = {0};
static Vector2 _playerVelocity = {0};
static float _playerRotation = 0;
static Vector2 _playerDirLine[2] = {0};

void ShowDebugMenu(void)
{
    if (IsKeyPressed(KEY_GRAVE))
    {
        _showDebugMenu = !_showDebugMenu;
    }

    if (_showDebugMenu)
    {
        // Rectangle r = {10, screenHeight - 100, 180, 80};
        // if (GuiButton(r, "Toggle Asteroid Count"))
        // {
        //     _showAsteroidCount = !_showAsteroidCount;
        // }
        //
        // r.x += 180 + 10;
        // if (GuiButton(r, "Show Angle Cone"))
        // {
        //     _showAngleCone = !_showAngleCone;
        // }

        Rectangle r = {10, SCREEN_HEIGHT - 40, 20, 20};
        GuiCheckBox(r, "Show Asteroid Count", &_showAsteroidCount);
        r.y -= 30;
        GuiCheckBox(r, "Show Projectile Count", &_showProjectileCount);
        r.y -= 30;
        GuiCheckBox(r, "Show Angle Cone", &_showAngleCone);
        r.y -= 30;
        GuiCheckBox(r, "Show Player Info", &_showPlayerInfo);
    }
}

void ShowDebugVisualizations(int asteroidCount, int projectileCount)
{
    if (_showAngleCone)
    {
        DrawLineV(line0[0], line0[1], RED);
        DrawLineV(line1[0], line1[1], BLUE);
    }

    if (_showAsteroidCount)
    {
        DrawRectangle(10, 10, 272, 52, Fade(BLACK, 0.6f));
        DrawText(TextFormat("ASTEROIDS: %d", asteroidCount), 20, 20, 32, WHITE);
    }

    if (_showProjectileCount)
    {
        DrawRectangle(10, 52, 272, 52, Fade(BLACK, 0.6f));
        DrawText(TextFormat("PROJECTILES: %d", projectileCount), 20, 20 + 52,
                 32, WHITE);
    }

    if (_showPlayerInfo)
    {
        DrawLineV(_playerDirLine[0], _playerDirLine[1], RED);
    }
}

void SetLastCone(Vector2 position, Vector2 velocity)
{
    line0[0] = position;
    line1[0] = position;

    line0[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                                  -ASTEROID_RANDOM_ANGLE));
    line1[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10),
                                                  ASTEROID_RANDOM_ANGLE));
}

void SetPlayerInfo(Vector2 position, Vector2 velocity, float rotation)
{
    _playerPosition = position;
    _playerVelocity = velocity;
    _playerRotation = rotation;

    Vector2 facingDirection =
        Vector2Rotate((Vector2){0, -1}, rotation * DEG2RAD);
    _playerDirLine[0] = position;
    _playerDirLine[1] = Vector2Add(position, Vector2Scale(facingDirection, 40));
}
