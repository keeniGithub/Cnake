#include <iostream>
#include <SDL3/SDL.h>
#include <chrono>
#include <thread>
#include <cstring>
#include <ctime>
#include <vector>

using namespace std;

char direction = 'W';
bool debugMode = false;
int score = 0;
int speed = 110;
int snake_size = 1;

bool check_border(SDL_Rect snake)
{
    if (snake.x < 0 || snake.x > 390 ||
        snake.y < 0 || snake.y > 390)
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

int main(int argc, char *args[])
{
    srand(time(0));
    vector<int> snake_x{};
    vector<int> snake_y{};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *myWindow = SDL_CreateWindow(
        "Cnake++",
        400,
        400,
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

                if (debugMode)
                {
                    cout << "x: " << snake.x << "\n";
                    cout << "y: " << snake.y << "\n";
                }

                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                case SDLK_a:
                    printf("left\n");
                    direction = 'A';
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    printf("right\n");
                    direction = 'D';
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    printf("down\n");
                    direction = 'S';
                    break;
                case SDLK_UP:
                case SDLK_w:
                    printf("up\n");
                    direction = 'W';
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
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

        if (!check_border(snake))
        {
            printf("end game\n");
            system("start https://yt3.googleusercontent.com/HWLGlrNtahx1qvGHMjLz_HQ1hlTGJjuUNRIeO49N3B8JwhqVu6SR7ap5mt1urs6xuKkcewDh=s900-c-k-c0x00ffffff-no-rj");
            return 0;
        }

        snake_x.insert(snake_x.begin(), snake.x);
        snake_x.resize(snake_size);
        snake_y.insert(snake_y.begin(), snake.y);
        snake_y.resize(snake_size);

        for (int i = 0; i < snake_size; i++)
        {
            int savex = snake.x;
            int savey = snake.y;
            snake.x = snake_x[i];
            snake.y = snake_y[i];
            cout << "x: " << snake_x[i] << endl;
            cout << "y: " << snake_y[i] << endl;
            SDL_FillSurfaceRect(myWindowSurface, &snake, SDL_MapRGB(myWindowSurface->format, 79, 100, 66));
            snake.x = savex;
            snake.y = savey;
        }

        delay(speed);

        if (snake.x == apple.x && snake.y == apple.y)
        {
            int rand_x = (rand() % 39) * 10;
            int rand_y = (rand() % 39) * 10;
            apple.x = rand_x;
            apple.y = rand_y;
            score += 10;
            if (speed >= 50)
                speed -= 3;
            snake.h += 10;

            cout << score << endl;
        }

        SDL_FillSurfaceRect(
            myWindowSurface,
            NULL,
            SDL_MapRGB(
                myWindowSurface->format,
                20,
                20,
                20));
        SDL_FillSurfaceRect(myWindowSurface, &snake, SDL_MapRGB(myWindowSurface->format, 79, 121, 66));
        SDL_FillSurfaceRect(myWindowSurface, &apple, SDL_MapRGB(myWindowSurface->format, 255, 83, 73));
        SDL_UpdateWindowSurface(myWindow);
    }

    SDL_DestroyWindow(myWindow);
    SDL_Quit();
    return 0;
}