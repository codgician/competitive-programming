#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 110

char arr[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int length, width, height;
        cin >> length >> width >> height;

        int row = (width << 1) + (height << 1) + 1;
        int column = (length << 1) + (width << 1) + 1;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                arr[i][j] = '.';
            }
        }

        // Upperside
        for (int i = 0; i < (width << 1) + 1; i++)
        {
            int startPos = (width << 1) - i;
            for (int j = startPos; j < startPos + (length << 1) + 1; j++)
            {
                if ((j - startPos) & 1)
                    arr[i][j] = (i & 1) ? '.' : '-';
                else
                    arr[i][j] = (i & 1) ? '/' : '+';
            }
        }

        // Front
        for (int i = (width << 1) + 1; i < row; i++)
        {
            for (int j = 0; j < (length << 1) + 1; j++)
            {
                if (j & 1)
                    arr[i][j] = ((i - (width << 1) - 1) & 1) ? '-' : '.';
                else
                    arr[i][j] = ((i - (width << 1) - 1) & 1) ? '+' : '|';
            }
        }

        // Rightside
        for (int j = column; j > column - (width << 1) - 1; j--)
        {
            int startPos = column - j;
            for (int i = startPos; i < startPos + (height << 1); i++)
            {
                if ((i - startPos) & 1)
                    arr[i][j] = ((column - j) & 1) ? '+' : '/';
                else
                    arr[i][j] = ((column - j) & 1) ? '|' : '.';
            }
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << arr[i][j];
            }
            cout << endl;
        }  
    }
    return 0;
}