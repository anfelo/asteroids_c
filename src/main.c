#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "game.h"
#include "raygui.h"
#include "vendors/raylib/raylib.h"

void UpdateDrawFrame(void);

bool _quitGame = false;

int main(void)
{
    srand(time(0));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
    InitGame();

    while (!WindowShouldClose() && !_quitGame)
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}

void UpdateDrawFrame(void)
{
    UpdateGame();

    BeginDrawing();
        ClearBackground(NEARBLACK);
        DrawGame();
    EndDrawing();
}
