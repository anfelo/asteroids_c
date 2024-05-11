#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define SCREEN_CENTER CLITERAL(Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}
#define SCREEN_AREA CLITERAL(Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}
#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define ASTEROIDS_MAX 64
#define ASTEROID_RANDOM_ANGLE 20 * DEG2RAD
#define ASTEROID_DELAY 1.5f

#endif
