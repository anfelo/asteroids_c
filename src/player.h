#ifndef PLAYER_H_
#define PLAYER_H_

#include "vendors/raylib/raylib.h"

#define PLAYER_RADIUS 20.0f

typedef enum PlayerState
{
    PLAYER_DEFAULT = 0,
    PLAYER_STUNNED,
    PLAYER_IFRAME,
    PLAYER_DEAD,
} PlayerState;

typedef struct Player
{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float lastFireTime;
    PlayerState state;
    float timeStateEntered;
} Player;

void PlayerMove(Player *player);
void PlayerDraw(Player player);
Vector2 PlayerFacingDirection(Player player);
void PlayerSetState(Player *player, PlayerState state);

#endif
