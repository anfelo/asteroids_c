#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "vendors/raylib/raylib.h"
#include "vendors/raylib/raymath.h"

typedef enum AsteroidSize {
    ASTEROID_SMALL = 1,
    ASTEROID_MEDIUM = 2,
    ASTEROID_LARGE = 4,
} AsteroidSize;

#define ASTEROID_ROT_SPEED_MIN 5
#define ASTEROID_ROT_SPEED_MAX 240

#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPEED_MAX 300

#define ASTEROID_LIFE 10.0f

typedef struct Asteroid {
    bool active;
    Vector2 position;
    float rotation;
    float rotationSpeed;
    Vector2 velocity;
    AsteroidSize size;
    float creationTime;
} Asteroid;

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
bool UpdateAsteroid(Asteroid *asteroid, float frametime, float time);
void DrawAsteroid(Asteroid asteroid);
float AsteroidRadius(Asteroid asteroid);

#endif
