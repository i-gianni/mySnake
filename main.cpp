#include "raylib.h"
#include<iostream>

using namespace std;

Color green {173, 204, 96, 255};
Color darkGreen {43,51,24,255};

int const cellSize{30};
int const cellCount{25};

class Food
{
    public:

    Vector2 position = {5,6};

    void Draw()
    {
        DrawRectangle(position.x * cellSize, position.y * cellSize,
            cellSize, cellSize, darkGreen);
    }
};


int main()
{
    int windowWidth{cellCount*cellSize};
    int windowHeight{cellCount*cellSize};
    //char const windowTitle{'Retro Snake'};

    int const FPS {60};

    cout << "Starting the game" << endl;
    
    InitWindow(windowWidth,windowHeight,"Retro Snake");

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