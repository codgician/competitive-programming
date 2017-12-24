#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 1001
using namespace std;

bool arr[SIZE][SIZE];  // Can walk?
bool hasVisited[SIZE][SIZE];

int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
int row, column;
int filledBlock = 0;

int getGcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return getGcd(b, a % b);
}

bool canMove(int nexti, int nextj)
{
    return nexti >= 0 && nexti < row && nextj >= 0 && nextj < column && arr[nexti][nextj];
}

void floodFill(int i, int j)
{
    arr[i][j] = false;
    filledBlock++;
    hasVisited[i][j] = true;

    for (int k = 0; k < 4; k++)
    {
        int nexti = i + di[k];
        int nextj = j + dj[k];
        if (canMove(nexti, nextj) && !hasVisited[nexti][nextj])
        {
            floodFill(nexti, nextj);
        }
    }

    hasVisited[i][j] = false;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column)
    {
        if (row == 0 && column == 0)
            break;

        int freeNum = 0;
        filledBlock = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                char ch;
                cin >> ch;
                if (ch == '.')
                {
                    arr[i][j] = true;
                    freeNum++;
                }
                else
                {
                    arr[i][j] = false;
                }
            }
        }

        memset(hasVisited, false ,sizeof(hasVisited));
        for (int j = 0; j < column; j++)
        {
            if (arr[0][j])
                floodFill(0, j);
            if (arr[row - 1][j])
                floodFill(row - 1, j);
        }
        for (int i = 1; i < row - 1; i++)
        {
            if (arr[i][0])
                floodFill(i, 0);
            if (arr[i][column - 1])
                floodFill(i, column - 1);
        }

        int gcd = getGcd(filledBlock, freeNum);
        cout << filledBlock / gcd << "/" << freeNum / gcd << endl;
    }
    return 0;
}
