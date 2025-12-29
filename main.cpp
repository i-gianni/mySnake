#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include <deque>
#include <filesystem>

using namespace std;

Color green {173, 204, 96, 255};
Color darkGreen {43,51,24,255};
int const offset {75};

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

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i],element)){return true;}
    }
    return false;
}

class Snake
{
public:

    deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
    Vector2 direction {1,0};
    bool addSegment {false};
    double speed {4.};

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{offset + x * cellSize, offset + y * cellSize, cellSize, cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update()
    {
        if(addSegment)
        {
            addSegment = false;
        }
        else
        {
            body.pop_back();
        }
        body.push_front(Vector2Add(body[0],direction));
    }

    void Reset()
    {
        body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
        direction = {1,0};
        speed = 4.;
    }
};

class Food
{
    public:

    Texture2D texture;
    Vector2 position;

    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("../graphics/baby.jpg");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        //DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
        DrawRectangle(offset + position.x * cellSize, offset + position.y * cellSize, cellSize, cellSize, darkGreen);
    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount -1);
        float y = GetRandomValue(0, cellCount -1);
        return Vector2 {x,y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomCell();
        if (ElementInDeque(position,snakeBody))
        {
            position = GenerateRandomCell();
        }
        return position;

    }
};

class Game
{
public:

    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score {0};
    Sound eatSound;
    Sound wallSound;

    Game()
    {
        InitAudioDevice();
        eatSound = LoadSound("../sounds/gnom.mp3");
        wallSound = LoadSound("../sounds/bonk.mp3");
    }

    ~Game()
    {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw()
    {
        snake.Draw();
        food.Draw();
    }

    void Update()
    {
        if(running)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void SnakeTurn()
    {
        if(IsKeyPressed(KEY_UP) && snake.direction.y != 1){
            snake.direction = {0, -1};
            running = true;
        }
        if(IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
        {
            snake.direction = {0, 1};
            running = true;
        }
        if(IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
        {
            snake.direction = {-1, 0};
            running = true;
        }
        if(IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
        {
            snake.direction = {1, 0};
            running = true;
        }
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(food.position,snake.body[0]))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            snake.speed ++;
            score ++;
            PlaySound(eatSound);
        }
    }

    void CheckCollisionWithEdges()
    {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1)
        {
            GameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void CheckCollisionWithTail()
    {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if(ElementInDeque(snake.body[0],headlessBody))
        {
            GameOver();
        }

    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
        PlaySound(wallSound);
    }
};

int main()
{
    constexpr int windowWidth{2*offset + cellCount*cellSize};
    constexpr int windowHeight{2*offset + cellCount*cellSize};
    const char *windowTitle{"Retro Snake"};

    int const FPS {60};

    InitWindow(windowWidth,windowHeight,windowTitle);
    SetTargetFPS(FPS);

    Game game = Game();

    while(WindowShouldClose() == false)
    {
        BeginDrawing();


        if(eventTriggered(1/game.snake.speed))
        {
            game.Update();
        }

        game.SnakeTurn();

        
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float) offset-5, (float) offset-5, (float) cellCount*cellSize+10, (float) cellCount*cellSize+10}, 5, darkGreen);
        DrawText("Retro Snake", offset-5, 20, 40, darkGreen);
        DrawText(TextFormat("%i",game.score), offset-5, offset + cellCount*cellSize+10, 40, darkGreen);
        game.Draw();

        EndDrawing();

    }

    CloseWindow();
    return 0;
}