//Made by Zuhad,Abdul rehman,Sadaqat yar khan.

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
 //used to prevent flicker


struct BrickRunner{

    void clearscreen()
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                                                            FOREGROUND_GREEN |
                                                            FOREGROUND_INTENSITY |
                                                            BACKGROUND_BLUE
                                                            );
        HANDLE hOut;
        COORD Position;

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        Position.X = 0;
        Position.Y = 0;
        SetConsoleCursorPosition(hOut, Position);
    }

};

int main()
{
  // declares a 2d array of 25*25 of char type.
  BrickRunner brick;
  char map[25][25];

    //loads the map with spaces and borders
    for(int i=0; i < 20; ++i) {
      for(int j=0; j < 20; ++j) {
        map[i][0] = 'Z';
        map[i][18] = 'Z';
        map[i][j] = ' ';
      }
    }

    int y = 17, x = 9; //the cars coordinates
    srand(time(0)); //Pseudo random number generator (function)
    int a = 0, b = rand() % 15 + 2; //the obstacles coordiantes (function)
    int points = 0; //points that the player has earned
    int speed = 200; //speed of the obstacles (and the car)
    int q = 0, p = rand() % 15 + 2; //the cash randomly generated
    int cashcheck = 0; //balances when the cash picked up
    int cashpickedup = 0;
    bool startup = true;

    char cash = '@';
    char obstacle = 220;

    char Brick = 'A';
    map[y][x] = Brick;
    //the game loop
    for(;;) {
      brick.clearscreen();
        //places the brick in centre
        map[y][x] = 'A';
        map[y][x+1] = ':';
        map[y][x-1] = ':';
        map[y+1][x-1] = 'O';
        map[y+1][x+1] = 'O';
        map[y-1][x-1] = 'O';
        map[y-1][x+1] = 'O';

      //makes the obstacles
      map[a][b] = ' ';
        map[a][b] = ' ';
        map[a][b+1] = ' ';
        map[a][b-1] = ' ';
        map[a+1][b-1] = ' ';
        map[a+1][b+1] = ' ';
        map[a-1][b-1] = ' ';
        map[a-1][b+1] = ' ';
        ++a;
        map[a][b] = obstacle;
        map[a][b+1] = obstacle;
        map[a][b-1] = obstacle;
        map[a+1][b-1] = obstacle;
        map[a+1][b+1] = obstacle;
        map[a-1][b-1] = obstacle;
        map[a-1][b+1] = obstacle;
        if(a > 20) {
          a = 0;
          b = rand() % 15 + 2;
        }
    //displays the map
    for(int i=0; i < 20; ++i) {
      for(int j=0; j < 20; ++j) {
        cout << map[i][j];
          if(j >= 19) {
            cout << endl;
          }
        }
      }
    cout << "    Points: " << points + (cashpickedup*30);
    //game starts after a key is pressed
    if(startup) {
      _getch();
      startup = false;
    }
    //moves the brick to the left
    if(GetAsyncKeyState(VK_LEFT)) {
      if(map[y][x-3] == obstacle) {
        goto lost;
      }
      else if(map[y][x-3] != 'Z') {
        map[y][x] = ' ';
        map[y][x+1] = ' ';
        map[y][x-1] = ' ';
        map[y+1][x-1] = ' ';
        map[y+1][x+1] = ' ';
        map[y-1][x-1] = ' ';
        map[y-1][x+1] = ' ';
        x -= 3;
        map[y][x] = 'Z';
        map[y][x+1] = 'Z';
        map[y][x-1] = 'Z';
        map[y+1][x-1] = 'O';
        map[y+1][x+1] = 'O';
        map[y-1][x-1] = 'O';
        map[y-1][x+1] = 'O';
      }
    }
    //moves the brick to the right
    if(GetAsyncKeyState(VK_RIGHT)) {
      if(map[y][x+3] == obstacle) {
        goto lost;
      }
      else if(map[y][x+3] != 'Z') {
        map[y][x] = ' ';
        map[y][x+1] = ' ';
        map[y][x-1] = ' ';
        map[y+1][x-1] = ' ';
        map[y+1][x+1] = ' ';
        map[y-1][x-1] = ' ';
        map[y-1][x+1] = ' ';
        x += 3;
        map[y][x] = 'A';
        map[y][x+1] = ':';
        map[y][x-1] = ':';
        map[y+1][x-1] = 'O';
        map[y+1][x+1] = 'O';
        map[y-1][x-1] = 'O';
        map[y-1][x+1] = 'O';
      }
    }
    //checks if the brick crashed
    if(map[y-2][x] == obstacle || map[y-2][x-1] == obstacle || map[y-2][x+1] == obstacle) {
lost:
      cout << "\n\nBrick Crashed\n" << endl;
      cin.get();
      return 0;
    }
    //checks if the player picked up cash
    if(map[y-2][x] == cash || map[y-2][x-1] == cash || map[y-2][x+1] == cash) {
      map[y-2][x] = ' ';
      map[y-2][x-1] = ' ';
      map[y-2][x+1] = ' ';
      ++cashpickedup;
      q = 0;
      p = rand() % 15 + 2;
    }
    //generates the cash
    else if(q > 20) {
      q = 0;
      p = rand() % 15 + 2;
    }
    //so cash doesnt appear next to the obstacle
    if(a > 8) {
      ++cashcheck;
    }
    //places the cash
    if(cashcheck) {
    map[q][p] = ' ';
    ++q;
    map[q][p] = cash;
    }
      ++points;
    //speeds up the obstacles each time the player gets another 100 points
    if(points == 100 || points == 200 || points == 300 || points == 400) {
        speed -= 20;
      }
    Sleep(speed);
    }
  return 0;
}

