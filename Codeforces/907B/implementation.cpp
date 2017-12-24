#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 9
using namespace std;

char arr[SIZE][SIZE];
int shitx[3] = {0, 3, 6};
int shity[3] = {0, 3, 6};

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, false ,sizeof(arr));
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cin >> arr[i][j];
        }
    }
    int lastx, lasty;
    cin >> lastx >> lasty;
    lastx--;
    lasty--;

    int startx = shitx[lastx % 3];
    int starty = shity[lasty % 3];

    bool isFull = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[startx + i][starty + j] == '.')
            {
                isFull = false;
                arr[startx + i][starty + j] = '!';
            }
        }
    }

    if (isFull)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (arr[i][j] == '.')
                {
                    arr[i][j] = '!';
                }
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << arr[i][j];
            if (j == 2 || j == 5)
                cout << " ";
        }
        if (i == 2 || i == 5)
            cout << endl;
        cout << endl;
    }

    return 0;
}
