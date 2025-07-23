#include <raylib.h>
#include <bits/stdc++.h>

using namespace std;

struct point {
    int x;
    int y;
};

double speed = 5;
int width = 1200;
int height = 800;
point p1, p2;
point ball;
double X = 5;
double Y = 5;
Color LBLUE {10, 140, 255 ,255};
int p1_score = 0, p2_score = 0;
int t;

void SETUP()
{
    t = 0;
    speed = 5;

    X = 5 * (int)pow(-1, rand() % 2);
    Y = 5  / (int)pow(2, (rand() % 2)) * (int)pow(-1, rand() % 2);

    ball.x = width / 2;
    ball.y = height / 2;
    p1.x = 10;
    p1.y = height / 2 - 60;
    p2.x = width - 35;
    p2.y = height / 2 - 60;
}

void BALL()
{
    DrawCircle(ball.x, ball.y, 20, WHITE);
    ball.x += X;
    ball.y += Y;
    if (CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, 20, Rectangle{(float)p1.x, (float)p1.y, 25, 120})) 
        X = -X;
    if (CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, 20, Rectangle{(float)p2.x, (float)p2.y, 25, 120})) 
        X = -X;
    if (ball.x < 0) {
        SETUP();
        p2_score ++;
    }
    if (ball.x > width + 20) {
        SETUP();
        p1_score ++;
    } 
    if (ball.y <= 20 || ball.y >= height - 20) {
        Y = -Y;
        ++t;
        if (t == 1) {
            speed += 1.25;
            if (X > 0) X += 1.25;
            else X -= 1.25;
            if (Y > 0) Y += 1.25;
            else Y -= 1.25;
            t = 0;
        }
    }
}

void PLAYER1()
{
    DrawText(TextFormat("%i", p1_score), width / 4 - 20, 20, 80, WHITE);
    DrawRectangle(p1.x, p1.y, 25, 120, WHITE);
    if (IsKeyDown(KEY_A) && p1.y < height - 120) {
        p1.y += speed;
    }
    if (IsKeyDown(KEY_Q) && p1.y > 0) {
        p1.y -= speed;
    }
}

void PLAYER2()
{
    DrawText(TextFormat("%i", p2_score), 3 * width / 4 - 20, 20, 80, WHITE);
    DrawRectangle(p2.x, p2.y, 25, 120, WHITE);
    if (IsKeyDown(KEY_L) && p2.y < height - 120) {
        p2.y += speed;
    }
    if (IsKeyDown(KEY_O) && p2.y > 0) {
        p2.y -= speed;
    }
}

int main()
{
    srand(time(0));
    SETUP();

    cout << "Starting the game!";

    InitWindow(width, height, "PONG GAME!");
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        DrawCircle(width / 2, height / 2, 181, LIGHTGRAY);
        DrawCircle(width / 2, height / 2, 180, LBLUE);
        PLAYER1();
        PLAYER2();
        DrawLine(width / 2, 0, width / 2, height, LIGHTGRAY);
        BALL();

        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}