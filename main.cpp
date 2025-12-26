#include "raylib.h"
#include <iostream>
#include <string>
#include <deque>

using namespace std;

Color green {173, 204, 96, 255};
Color darkGreen {43,51,24,255};

int const cellSize{30};
int const cellCount{25};

class Snake
{
public:

    deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, cellSize, cellSize};
            DrawRectangleRounded (segment, 0.5, 6, darkGreen);
        }
    }
};


class Food
{
    public:

    Texture2D texture;
    Vector2 position;

    Food()
    {
        Image image = LoadImage("/home/ivang/repos/mySnake/graphics/baby.jpg");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, cellCount -1);
        float y = GetRandomValue(0, cellCount -1);
        return Vector2{x,y};

    }
};


int main()
{
    constexpr int windowWidth{cellCount*cellSize};
    constexpr int windowHeight{cellCount*cellSize};
    const char *windowTitle{"Retro Snake"};

    int const FPS {60};

    cout << "Starting the game" << endl;

    InitWindow(windowWidth,windowHeight,windowTitle);
    SetTargetFPS(FPS);

    Food food = Food();
    Snake snake = Snake();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green);

        food.Draw();
        snake.Draw();


        EndDrawing();

    }

    CloseWindow();
    return 0;
}