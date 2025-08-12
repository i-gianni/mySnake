#include "raylib.h"
#include<iostream>
#include<string>

using namespace std;

Color green {173, 204, 96, 255};
Color darkGreen {43,51,24,255};

int constexpr cellSize{30};
int constexpr cellCount{25};

class Food
{
    public:

    Vector2 position = {rand() % cellCount, rand() % cellCount};

    void Draw()
    {
        DrawRectangle(position.x * cellSize, position.y * cellSize,
            cellSize, cellSize, darkGreen);
    }
};


int main()
{
    srand(time(0));

    constexpr int windowWidth{cellCount*cellSize};
    constexpr int windowHeight{cellCount*cellSize};
    const char *windowTitle{"Retro Snake"};

    int const FPS {60};

    cout << "Starting the game" << endl;

    InitWindow(windowWidth,windowHeight,windowTitle);

    SetTargetFPS(FPS);

    Food food = Food();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green);

        food.Draw();

        EndDrawing();

    }

    CloseWindow();
    return 0;
}