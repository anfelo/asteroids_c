#include "player.h"
#include "constants.h"
#include "debug.h"
#include "vendors/raylib/raylib.h"
#include "vendors/raylib/raymath.h"
#include <stdio.h>

#define PLAYER_ROT_SPEED 360
#define PLAYER_SPEED 250
#define PLAYER_ACCELERATION 750
#define PLAYER_DECELERATION 175
#define PLAYER_NUDGE_VELOCITY 150

#define FIELD_MIN_X (-PLAYER_RADIUS)
#define FIELD_MAX_X (SCREEN_WIDTH + PLAYER_RADIUS)
#define FIELD_MIN_Y (-PLAYER_RADIUS)
#define FIELD_MAX_Y (SCREEN_HEIGHT + PLAYER_RADIUS)

static void UpdateAngle(Player *player, float frametime)
{
    int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    player->rotation += (xIn * PLAYER_ROT_SPEED * frametime);
}

static void UpdateVelocity(Player *player, float frametime)
{
    int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
    float magSqr = Vector2LengthSqr(player->velocity);
    float mag = sqrt(magSqr);
    Vector2 facingDirection = PlayerFacingDirection(*player);

    if (yIn > 0)
    {
        player->velocity = Vector2Add(
            player->velocity,
            Vector2Scale(facingDirection, PLAYER_ACCELERATION * frametime));
        if (mag > PLAYER_SPEED)
        {
            player->velocity =
                Vector2Scale(player->velocity, PLAYER_SPEED / mag);
        }
    }
    else
    {
        if (mag > 0)
        {
            float xSign = (player->velocity.x < 0) ? -1.0f : 1.0f;
            float ySign = (player->velocity.y < 0) ? -1.0f : 1.0f;

            float xAbs = player->velocity.x * xSign;
            float yAbs = player->velocity.y * ySign;

            float xWeight = xAbs * xAbs / magSqr;
            float yWeight = yAbs * yAbs / magSqr;

            float xDecel = xWeight * PLAYER_DECELERATION * xSign * frametime;
            float yDecel = yWeight * PLAYER_DECELERATION * ySign * frametime;

            player->velocity.x =
                (xAbs > xDecel) ? player->velocity.x - xDecel : 0;
            player->velocity.y =
                (yAbs > yDecel) ? player->velocity.y - yDecel : 0;
        }
    }
}

static void UpdateWrap(Player *player, float frametime)
{
    if (player->position.x > FIELD_MAX_X)
    {
        player->position.x = -PLAYER_RADIUS;
        if (player->velocity.x < PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.x = PLAYER_NUDGE_VELOCITY;
        }
    }
    else if (player->position.x < FIELD_MIN_X)
    {
        player->position.x = SCREEN_WIDTH + PLAYER_RADIUS;
        if (player->velocity.x > -PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.x = -PLAYER_NUDGE_VELOCITY;
        }
    }

    if (player->position.y > FIELD_MAX_Y)
    {
        player->position.y = -PLAYER_RADIUS;
        if (player->velocity.y < PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.y = PLAYER_NUDGE_VELOCITY;
        }
    }
    else if (player->position.y < FIELD_MIN_Y)
    {
        player->position.y = SCREEN_HEIGHT + PLAYER_RADIUS;
        if (player->velocity.y > -PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.y = -PLAYER_NUDGE_VELOCITY;
        }
    }
}

void PlayerMove(Player *player)
{
    float frametime = GetFrameTime();

    if (player->state != PLAYER_STUNNED && player->state != PLAYER_DEAD)
    {
        UpdateAngle(player, frametime);
        UpdateVelocity(player, frametime);
    }

    player->position =
        Vector2Add(player->position, Vector2Scale(player->velocity, frametime));
    UpdateWrap(player, frametime);

    SetPlayerInfo(player->position, player->velocity, player->rotation);
}

void PlayerDraw(Player player)
{
    if (player.state == PLAYER_DEAD)
    {
        return;
    }

    Vector2 p[6] = {
        (Vector2){0.0f, -1.0f}, (Vector2){-1.0f, 1.0f}, (Vector2){-0.4f, 0.6f},
        (Vector2){0.4f, 0.6f},  (Vector2){1.0f, 1.0f},  (Vector2){0.0f, -1.0f},
    };
    size_t len = sizeof(p) / sizeof(p[0]);

    Color color = WHITE;
    if (player.state == PLAYER_IFRAME)
    {
        float seconds = GetTime() - player.timeStateEntered;
        int value = (int)(seconds * 6.0f);
        if (value % 2)
        {
            color = Fade(RED, 0.3f);
        }
    }

    for (int i = 0; i < len; i++)
    {
        DrawLineEx(
            Vector2Add(
                Vector2Scale(Vector2Rotate(p[i], player.rotation * DEG2RAD),
                             PLAYER_RADIUS),
                player.position),
            Vector2Add(Vector2Scale(Vector2Rotate(p[(i + 1) % len],
                                                  player.rotation * DEG2RAD),
                                    PLAYER_RADIUS),
                       player.position),
            2.0f, color);
    }
}

Vector2 PlayerFacingDirection(Player player)
{
    return Vector2Rotate((Vector2){0, -1}, player.rotation * DEG2RAD);
}

void PlayerSetState(Player *player, PlayerState state)
{
    player->state = state;
    player->timeStateEntered = GetTime();
}
