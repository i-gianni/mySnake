#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <deque>
#include <filesystem>

using namespace std;

Color green {173, 204, 96, 255};
Color darkGreen {43,51,24,255};

int const cellSize{30};
int const cellCount{25};

double lastUpdateTime {0.};

void pwd()
{
    // finding and printing the current working directory.
    cout << "Current path is " << filesystem::current_path()
         << endl;
    return;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;

}


class Snake
{
public:

    deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
    Vector2 direction {1,0};

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

    void Update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0],direction));
    }
};

class Food
{
    public:

    Texture2D texture;
    Vector2 position;

    Food()
    {
        Image image = LoadImage("../graphics/baby.jpg");
        texture = LoadTextureFromImage(image);
        //texture = LoadTexture("../graphics/baby.jpg");
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        //DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, cellCount -1);
        float y = GetRandomValue(0, cellCount -1);
        return Vector2{x,y};

    }
};

class Game
{
public:

    Snake snake = Snake();
    Food food = Food();

    void Draw()
    {
        snake.Draw();
        food.Draw();
    }

    void Update()
    {
        snake.Update();
    }

    void SnakeTurn()
    {
        if(IsKeyPressed(KEY_UP) && snake.direction.y != 1){snake.direction = {0, -1};}
        if(IsKeyPressed(KEY_DOWN) && snake.direction.y != -1){snake.direction = {0, 1};}
        if(IsKeyPressed(KEY_LEFT) && snake.direction.x != 1){snake.direction = {-1, 0};}
        if(IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1){snake.direction = {1, 0};}
    }
};

int main()
{
    constexpr int windowWidth{cellCount*cellSize};
    constexpr int windowHeight{cellCount*cellSize};
    const char *windowTitle{"Retro Snake"};

    int const FPS {60};

    InitWindow(windowWidth,windowHeight,windowTitle);
    SetTargetFPS(FPS);

    Game game = Game();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();


        if(eventTriggered(0.2))
        {
            game.Update();
        }

        game.SnakeTurn();

        
        ClearBackground(green);

        game.Draw();

        EndDrawing();

    }

    CloseWindow();
    return 0;
}