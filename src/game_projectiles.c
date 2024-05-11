#include "game_projectiles.h"
#include "constants.h"
#include "game_asteroids.h"
#include "projectile.h"
#include "vendors/raylib/raylib.h"

#define PROJECTILE_MAX 12

static Projectile _projectiles[PROJECTILE_MAX];

static bool CheckCollisionProjectile(Projectile *projectile, Asteroid *asteroid)
{
    return asteroid->active &&
           CheckCollisionPointCircle(projectile->position, asteroid->position,
                                     AsteroidRadius(*asteroid));
}

void AddProjectile(Vector2 position, float rotation)
{
    for (int i = 0; i < PROJECTILE_MAX; i++)
    {
        if (_projectiles[i].active)
        {
            continue;
        }

        _projectiles[i] = CreateProjectile(position, rotation);
        return;
    }

    TraceLog(LOG_ERROR, "Failed to create a projectile because there was "
                        "no inactive spots in the array!");
}

int UpdateProjectiles(void)
{
    float frametime = GetFrameTime();
    float time = GetTime();

    Asteroid *asteroids = AsteroidsArray();

    int projectileCount = 0;
    for (int i = 0; i < PROJECTILE_MAX; i++)
    {
        Projectile *projectile = _projectiles + i;
        if (ProjectileUpdate(projectile, frametime, time))
        {
            projectileCount++;

            for (int j = 0; j < ASTEROIDS_MAX; j++)
            {
                Asteroid *asteroid = asteroids + j;
                if (CheckCollisionProjectile(projectile, asteroid))
                {
                    DestroyAsteroid(j);
                    projectile->active = false;

                    break;
                }
            }
        }
    }

    return projectileCount;
}

void DrawProjectiles(void)
{
    for (int i = 0; i < PROJECTILE_MAX; i++)
    {
        ProjectileDraw(_projectiles[i]);
    }
}

void ResetProjectiles(void)
{
    for (int i = 0; i < PROJECTILE_MAX; i++)
    {
        _projectiles[i] = (Projectile){0};
    }
}
