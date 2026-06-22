#include<iostream>
#include<conio.h>
#include<string>
#include<chrono>
#include<thread>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<random>

#define Row 15
#define Col 35

int foox, fooy, score = 0, choice;

void food(std::vector<std::pair<int,int>> &snake)
{
    bool overlap = true;

    while(overlap)
    {
        overlap = false;

        foox = rand() % (Row - 2) + 1;
        fooy = rand() % (Col - 2) + 1;

        for(auto p : snake)
        {
            if(p.first == foox && p.second == fooy)
            {
                overlap = true;
                break;
            }
        }
    }
}

void control(std::vector<std::pair<int,int>> &snake, char dir)
{
    int x = snake[0].first;
    int y = snake[0].second;

    if(dir == 'w')
        x--;

    else if(dir == 's')
        x++;

    else if(dir == 'a')
        y--;

    else if(dir == 'd')
        y++;

    snake.insert(snake.begin(), {x,y});

    if(x == foox && y == fooy)
    {
        food(snake);
        score += 3;
    }
    else
    {
        snake.pop_back();
    }
}

bool condition(std::vector<std::pair<int,int>> &snake)
{
    int x = snake[0].first;
    int y = snake[0].second;

    if(x >= Row - 1 || x <= 0 || y <= 0 || y >= Col - 1)
        return true;

    for(int i = 1; i < snake.size(); i++)
    {
        if(snake[i].first == x &&
           snake[i].second == y)
        {
            return true;
        }
    }

    return false;
}

void screen(char canvas[Row][Col],
            std::vector<std::pair<int,int>> &snake)
{
    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Col; j++)
        {
            if(j == 0 || j == Col - 1)
            {
                canvas[i][j] = char(219);
            }

            else if((i == 0 || i == Row - 1) /*&&
                    (j % 2 == 0)*/)
            {
                canvas[i][j] = char(219);
            }

            else
            {
                canvas[i][j] = ' ';
            }
        }
    }

    for(auto p : snake)
    {
        canvas[p.first][p.second] = 'O';
    }

    canvas[foox][fooy] = '$';
}

void display(char canvas[Row][Col])
{
    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Col; j++)
        {
            std::cout << canvas[i][j];
        }

        std::cout << std::endl;
    }
}

void game(char canvas[Row][Col],
          std::vector<std::pair<int,int>> &snake)
{
    char dir = ' ';
    int rid = ' ';

    int speed;

    if(choice == 1)
        speed = 150;

    else if(choice == 2)
        speed = 100;

    else
        speed = 50;

    while(true)
    {
        screen(canvas, snake);

        std::cout << "Score: " << score << "\n";

        display(canvas);

        if(_kbhit())
        {
            rid = _getch();

            if(rid == 0 || rid == 224)
            {
                rid = _getch();

                if(rid == 72 && dir != 's')
                    dir = 'w';

                else if(rid == 80 && dir != 'w')
                    dir = 's';

                else if(rid == 75 && dir != 'd')
                    dir = 'a';

                else if(rid == 77 && dir != 'a')
                    dir = 'd';
            }

            else
            {
                if(rid == 'q' || rid == 'Q')
                {
                    std::cout << "Thank you for playing!\n";
                    std::cout << "Score: " << score;
                    exit(0);
                }

                if((rid == 'w' || rid == 'W') &&
                   dir != 's')
                {
                    dir = 'w';
                }

                else if((rid == 's' || rid == 'S') &&
                        dir != 'w')
                {
                    dir = 's';
                }

                else if((rid == 'a' || rid == 'A') &&
                        dir != 'd')
                {
                    dir = 'a';
                }

                else if((rid == 'd' || rid == 'D') &&
                        dir != 'a')
                {
                    dir = 'd';
                }
            }
        }

        if(dir != ' ')
        {
            control(snake, dir);
        }

        if(condition(snake))
            break;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(speed)
        );

        system("cls");
    }
}

int main()
{   char again;
    srand(time(0));
    while(true){
    std::vector<std::pair<int,int>> snake;

    snake.push_back({8,7});
    snake.push_back({8,6});
    snake.push_back({8,5});

    char canvas[Row][Col];

    food(snake);

    std::cout << "Welcome to The Python!\n";
    std::cout << "Use WASD / Arrow Keys to control the Python.\n";
    std::cout << "Press Q to quit.\n\n";

    std::cout << "You're a...:\n";
    std::cout << "1) Beginner\n";
    std::cout << "2) Semi Professional\n";
    std::cout << "3) Professional\n";

    while(true)
    {
        std::cin >> choice;

        if(choice >= 1 && choice <= 3)
            break;

        std::cout << "Invalid Choice! Enter again:(1-3)\n";
    }

    system("cls");

    game(canvas, snake);

    std::cout << "Oh My God! Game Over!\n";
    std::cout << "Score: " << score<<std::endl;
    std::cout << "Press Y to try again or N to quit:\n";
    std::cin  >> again;
   
    if(again == 'y' || again == 'Y')
    {
        system("cls");
        continue;
    }
    else
    {
        std::cout << "Thank you for playing!\n";
        break;
    }
    }
    return 0;
}