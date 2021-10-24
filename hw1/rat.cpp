#include <iostream>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

// read the maze and print out
void print_maze(int maze[][17])
{
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            printf("%d", maze[i][j]);
        }
        printf("\n");
    }
}

// reset the maze to initial state
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

// to determine whether the path is found
bool flag = false;

// the direction to go in order right -> down -> up -> left
int x_move[4] = {0, 1, -1, 0};
int y_move[4] = {1, 0, 0, -1};

// element stored in stack
struct Items
{
    //constructor
    Items(int x_input, int y_input, int dir_input) : x{x_input}, y{y_input}, dir{dir_input} {}
    int x, y, dir;
};

void Path(int startx, int starty, const int m, const int p, int maze[][17], int mark[][17])
{
    // to count steps the rat in maze walk
    int count = 0;

    // initialize stack to the maze entrance coordinates and direction right
    mark[startx][starty] = 1;
    stack<Items> s;
    Items temp(startx, starty, 0);
    s.push(temp);

    // if still path left
    while (!s.empty())
    {
        temp = s.top();
        s.pop();

        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;

        // count +1 for every step
        cout << count << ":" << i << "," << j << endl;
        count++;

        // try four direction each point
        while (d < 4)
        {
            // the next point to go
            int g = i + x_move[d], h = j + y_move[d];

            //reached exit
            if (g == m && h == p)
            {
                flag = true; // find path

                cout << count << ":" << g << "," << h << endl;
                cout << "successfully escaped!!\n"
                     << endl;
                return;
            }

            // legal move and haven't been here before
            if (!maze[g][h] && !mark[g][h])
            {

                // mark visited point
                mark[g][h] = 1;

                //the direction to go when visit this point again
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                s.push(temp);

                cout << count << ":" << g << "," << h << endl;
                count++;

                // move from (i, j) to (g, h)
                i = g;
                j = h;
                d = 0;
            }
            else
                d++; // try next direction
        }
    }
}

int main()
{
    int maze[17][17], mark[17][17];

    // read maze by line and print out
    cout << "enter file name : ";
    string filename, text;
    cin >> filename;

    ifstream readFile(filename);
    for (int i = 0; getline(readFile, text); i++)
    {
        for (int j = 0; j < text.length(); j++)
        {
            maze[i][j] = (int)text[j] - '0';
            mark[i][j] = maze[i][j];
        }
    }
    readFile.close();
    print_maze(maze);

    // record entrance and exit repeatedly
    int startX, startY, endX, endY;
    while (true)
    {
        cout << "enter start position : ";
        cin >> startX >> startY;

        // end when entrance = (-1, -1)
        if (startX == -1 && startY == -1)
        {
            printf("end the code.");
            return 0;
        }
        cout << "enter exit position : ";
        cin >> endX >> endY;

        flag = false; // yet to find path
        Path(startX, startY, endX, endY, maze, mark);
        reset_maze(mark, maze);
        if (!flag)
            cout << "Failed to escape.\n"
                 << endl;
    }
}
