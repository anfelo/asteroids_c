#include "game_asteroids.h"
#include "asteroid.h"
#include "constants.h"
#include "debug.h"
#include "game_score.h"
#include "vendors/raylib/raymath.h"

static AsteroidSize _asteroid_sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                         ASTEROID_LARGE};
static Asteroid _asteroids[ASTEROIDS_MAX] = {0};
static float _lastAsteroidCreationTime = -1.0f;

Asteroid *AsteroidsArray(void)
{
    return _asteroids;
}

void ResetAsteroids(void)
{
    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        _asteroids[i] = (Asteroid){0};
        _lastAsteroidCreationTime = -1.0f;
    }
}

int UpdateAsteroids(void)
{
    int activeAsteroids = 0;

    float frametime = GetFrameTime();
    float time = GetTime();

    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        if (UpdateAsteroid(_asteroids + i, frametime, GetTime()))
        {
            activeAsteroids++;
        }
    }

    if (time > _lastAsteroidCreationTime + ASTEROID_DELAY)
    {
        AsteroidSize nextSize = _asteroid_sizes[GetRandomValue(0, 2)];
        AddAsteroid(GetNextAsteroidPosition(), nextSize, 1.0f, true);
        _lastAsteroidCreationTime = time;
    }

    return activeAsteroids;
}

void DrawAsteroids(void)
{
    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        DrawAsteroid(_asteroids[i]);
    }
}

void AddAsteroid(Vector2 position, AsteroidSize size, float speedMod,
                 bool spawn)
{
    Vector2 velocity =
        spawn ? Vector2Subtract(SCREEN_CENTER, position)
              : Vector2Rotate((Vector2){0, 1}, (float)GetRandomValue(0, 359));

    velocity = Vector2Scale(
        Vector2Normalize(velocity),
        speedMod * GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX));

    SetLastCone(position, velocity);

    velocity =
        Vector2Rotate(velocity, (float)GetRandomValue(-ASTEROID_RANDOM_ANGLE,
                                                      ASTEROID_RANDOM_ANGLE));

    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        if (_asteroids[i].active)
        {
            continue;
        }

        _asteroids[i] = CreateAsteroid(position, velocity, size);
        return;
    }

    TraceLog(LOG_ERROR, "Failed to create an asteroid because there was no "
                        "inactive spots in the array!");
}

void DestroyAsteroid(int index)
{
    const float largeSpeedMod = 0.5f;
    const float mediumSpeedMod = 0.33f;

    Asteroid *asteroid = _asteroids + index;
    asteroid->active = false;

    int points = ASTEROID_BASE_SCORE * (int)asteroid->size;
    switch (asteroid->size)
    {
    case ASTEROID_LARGE:
        AddAsteroid(asteroid->position, ASTEROID_MEDIUM, largeSpeedMod, false);
        AddAsteroid(asteroid->position, ASTEROID_MEDIUM, largeSpeedMod, false);
        break;
    case ASTEROID_MEDIUM:
        AddAsteroid(asteroid->position, ASTEROID_SMALL, mediumSpeedMod, false);
        AddAsteroid(asteroid->position, ASTEROID_SMALL, mediumSpeedMod, false);
        break;
    default:
        break;
    }

    if (points <= 0)
    {
        TraceLog(LOG_ERROR, "Tried to add 0 or negative points to score.");
    }
    AddScore(points);
}

Vector2 GetNextAsteroidPosition(void)
{
    int padding = 128;
    Vector2 result = {-padding, -padding};

    if (GetRandomValue(0, 1))
    {
        if (GetRandomValue(0, 1))
        {
            result.y = SCREEN_HEIGHT + padding;
        }

        result.x = GetRandomValue(-padding, SCREEN_WIDTH + padding);
    }
    else
    {
        if (GetRandomValue(0, 1))
        {
            result.x = SCREEN_WIDTH + padding;
        }

        result.y = GetRandomValue(-padding, SCREEN_HEIGHT + padding);
    }

    return result;
}
