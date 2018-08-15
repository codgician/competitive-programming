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

#define DIR_CLOCKWISE 0
#define DIR_COUNTER 1

#define SIZE 3

char arr[SIZE][SIZE];
char tmp[SIZE][SIZE];

void rotate(int x1, int y1, int x2, int y2, bool dir)
{
    if (dir == DIR_CLOCKWISE)
    {
        tmp[x1][y1] = arr[x2][y1];
        tmp[x1][y2] = arr[x1][y1];
        tmp[x2][y1] = arr[x2][y2];
        tmp[x2][y2] = arr[x1][y2];
    }
    else
    {
        tmp[x1][y1] = arr[x1][y2];
        tmp[x1][y2] = arr[x2][y2];
        tmp[x2][y1] = arr[x1][y1];
        tmp[x2][y2] = arr[x2][y1];
    }

    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            arr[i][j] = tmp[i][j];
        }
    }
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int qNum;
        scanf("%d", &qNum);
        for (int i = 0; i < SIZE; i++)
        {
            scanf("%s", arr[i]);
        }

        while (qNum--)
        {
            char buf[10];
            scanf("%s", buf);

            int x1, y1, x2, y2;
            if (buf[0] == '1')
            {
                x1 = 0, y1 = 0;
                x2 = 1, y2 = 1;
            }
            else if (buf[0] == '2')
            {
                x1 = 0, y1 = 1;
                x2 = 1, y2 = 2;
            }
            else if (buf[0] == '3')
            {
                x1 = 1, y1 = 0;
                x2 = 2, y2 = 1;
            }
            else
            {
                x1 = 1, y1 = 1;
                x2 = 2, y2 = 2;
            }

            if (buf[1] == 'C')
                rotate(x1, y1, x2, y2, DIR_CLOCKWISE);
            else
                rotate(x1, y1, x2, y2, DIR_COUNTER);
        }

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                printf("%c", arr[i][j]);
            }
            printf("\n");
        }

    }
    return 0;
}