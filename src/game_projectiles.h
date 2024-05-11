#ifndef PROJECTILES_H_
#define PROJECTILES_H_

#include "projectile.h"

void AddProjectile(Vector2 position, float rotation);
int UpdateProjectiles(void);
void DrawProjectiles(void);
void ResetProjectiles(void);

#endif
