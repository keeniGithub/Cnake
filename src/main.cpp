#include <iostream>
#include <SDL3/SDL.h>
#include <chrono>
#include <thread>
#include <cstring>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

char direction = 'W';
bool debugMode = false;
int score = 0;
int speed = 110;
int snakeSize = 3;
int winSize = 700;

bool check_border(SDL_Rect snake)
{
    if (snake.x < 0 || snake.x > winSize - 10 ||
        snake.y < 0 || snake.y > winSize - 10)
    {
        return false;
    }
    return true;
    // false - если граница достигнута
    // true - если все окей
}

void delay(int time)
{
    this_thread::sleep_for(chrono::milliseconds(time));
}

void loop_move(SDL_Rect snake, char direction)
{
    if (direction == 'A')
    {
        snake.x -= 10;
    }
    else if (direction == 'D')
    {
        snake.x += 10;
    }
    else if (direction == 'W')
    {
        snake.y -= 10;
    }
    else if (direction == 'S')
    {
        snake.y += 10;
    }
}

bool isSnakeInVectors(const vector<int> &snake_x, const vector<int> &snake_y)
{
    if (snake_x.empty() || snake_y.empty())
    {
        return false;
    }

    int head_x = snake_x.front();
    int head_y = snake_y.front();

    for (size_t i = 1; i < snake_x.size(); i++)
    {
        if (snake_x[i] == head_x && snake_y[i] == head_y)
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char *args[])
{
    srand(time(0));
    vector<int> snake_x{};
    vector<int> snake_y{};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *myWindow = SDL_CreateWindow(
        "Cnake++",
        winSize,
        winSize,
        0);
    SDL_Surface *myWindowSurface = SDL_GetWindowSurface(myWindow);
    SDL_FillSurfaceRect(
        myWindowSurface,
        NULL,
        SDL_MapRGB(
            myWindowSurface->format,
            20,
            20,
            20));

    SDL_Rect snake;
    snake.x = 200;
    snake.y = 200;
    snake.w = 10;
    snake.h = 10;
    SDL_FillSurfaceRect(
        myWindowSurface,
        &snake,
        SDL_MapRGB(
            myWindowSurface->format,
            20,
            20,
            20));

    SDL_Rect apple;
    apple.w = 10;
    apple.h = 10;
    int rand_x = (rand() % 40 + 1) * 10;
    int rand_y = (rand() % 40 + 1) * 10;
    apple.x = rand_x;
    apple.y = rand_y;

    SDL_FillSurfaceRect(
        myWindowSurface,
        &apple,
        SDL_MapRGB(
            myWindowSurface->format,
            20,
            20,
            20));

    SDL_UpdateWindowSurface(myWindow);
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event)) // пока просиходят события
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                quit = true;
                break;

            case SDL_EVENT_KEY_DOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                case SDLK_a:
                    printf("left\n");
                    if (direction != 'D')
                    {
                        direction = 'A';
                    }
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    printf("right\n");
                    if (direction != 'A')
                    {
                        direction = 'D';
                    }
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    printf("down\n");
                    if (direction != 'W')
                    {
                        direction = 'S';
                    }
                    break;
                case SDLK_UP:
                case SDLK_w:
                    printf("up\n");
                    if (direction != 'S')
                    {
                        direction = 'W';
                    }
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        if (snake.x == apple.x && snake.y == apple.y)
        {
            int rand_x = (rand() % 39) * 10;
            int rand_y = (rand() % 39) * 10;
            apple.x = rand_x;
            apple.y = rand_y;
            score += 10;
            snakeSize++;

            if (speed >= 50)
                speed -= 3;

            cout << score << endl;
        }

        if (direction == 'A')
        {
            snake.x -= 10;
        }
        else if (direction == 'D')
        {
            snake.x += 10;
        }
        else if (direction == 'W')
        {
            snake.y -= 10;
        }
        else if (direction == 'S')
        {
            snake.y += 10;
        }

        if (!check_border(snake) || isSnakeInVectors(snake_x, snake_y))
        {
            printf("end game\n");
            system("start https://yt3.googleusercontent.com/HWLGlrNtahx1qvGHMjLz_HQ1hlTGJjuUNRIeO49N3B8JwhqVu6SR7ap5mt1urs6xuKkcewDh=s900-c-k-c0x00ffffff-no-rj");
            return 0;
        }

        snake_x.insert(snake_x.begin(), snake.x);
        snake_x.resize(snakeSize);
        snake_y.insert(snake_y.begin(), snake.y);
        snake_y.resize(snakeSize);

        delay(speed);

        SDL_FillSurfaceRect(
            myWindowSurface,
            NULL,
            SDL_MapRGB(
                myWindowSurface->format,
                20,
                20,
                20));
        SDL_FillSurfaceRect(myWindowSurface, &apple, SDL_MapRGB(myWindowSurface->format, 255, 83, 73));

        for (int i = 0; i < snakeSize; i++)
        {
            int savex = snake.x;
            int savey = snake.y;
            snake.x = snake_x[i];
            snake.y = snake_y[i];
            SDL_FillSurfaceRect(myWindowSurface, &snake, SDL_MapRGB(myWindowSurface->format, 79, 100, 66));
            snake.x = savex;
            snake.y = savey;
        }

        SDL_UpdateWindowSurface(myWindow);
    }

    SDL_DestroyWindow(myWindow);
    SDL_Quit();
    return 0;
}