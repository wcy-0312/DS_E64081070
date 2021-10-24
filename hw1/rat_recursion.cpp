#include <iostream>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

void path(int, int, int, int, int[][17]);
void print_maze(int maze[][17])
{
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}
void reset_maze(int maze[][17], int copy[][17])
{
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            maze[i][j] = copy[i][j];
        }
    }
}
bool flag = false;

int count = 0;

int main()
{
    int copy[17][17], maze[17][17];

    cout << "enter file name : ";
    string filename, text;
    cin >> filename;

    ifstream readFile(filename);
    for (int i = 0; getline(readFile, text); i++)
    {
        for (int j = 0; j < text.length(); j++)
        {
            maze[i][j] = (int)text[j] - '0';
            copy[i][j] = maze[i][j];
        }
    }
    readFile.close();
    print_maze(maze);

    int startX, startY, endX, endY;
    while (true)
    {
        cout << "enter start position : ";
        cin >> startX >> startY;
        if (startX == -1 && startY == -1)
        {
            printf("end the code.");
            return 0;
        }
        cout << "enter exit position : ";
        cin >> endX >> endY;

        flag = false;
        count = 0;
        path(startX, startY, endX, endY, maze);
        reset_maze(maze, copy);
        print_maze(maze);
        if (!flag)
            printf("Failed to escape.\n");
    }
}

void path(int sx, int sy, int ex, int ey, int maze[][17])
{
    if (flag)
        return;

    maze[sx][sy] = 1;
    printf("%d : (%d,%d)\n", count, sy, sx);
    count++;
    if (sx == ex && sy == ey)
    {
        printf("successfully escaped!!\n");
        flag = true;
        return;
    }

    if (!maze[sx + 1][sy]) // move down
        path(sx + 1, sy, ex, ey, maze);

    if (!maze[sx][sy + 1]) // move right
        path(sx, sy + 1, ex, ey, maze);

    if (!maze[sx - 1][sy]) // move up
        path(sx - 1, sy, ex, ey, maze);

    if (!maze[sx][sy - 1]) // move left
        path(sx, sy - 1, ex, ey, maze);

    else
    {
        maze[sx][sy] = 1;
        return;
    }
}