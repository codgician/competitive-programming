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

#define SIZE 51

char arr[SIZE][20];
int freeNum[SIZE];

int prior[5] = {4, 2, 0, 5, 1};

int main()
{
    int row, num;
    while (scanf("%d%d", &row, &num) != EOF)
    {
        row += 3;
        memset(freeNum, 0, sizeof(freeNum));
        int leftWeight = 0, rightWeight = 0;
        for (int i = 0; i < row; i++)
        {
            scanf("%s", arr[i]);

            for (int j = 0; j < 12; j++)
            {
                if (arr[i][j] == '-')
                {
                    freeNum[i]++;
                }
                else if (arr[i][j] == '#')
                {
                    if (j < 5)
                        leftWeight++;
                    else if (j > 5)
                        rightWeight++;
                }
            }
        }

        for (int i = 0; i < num; i++)
        {
            // Locate row
            bool ignoreOthers = false;
            if (freeNum[1] > 0 || freeNum[((row - 3) >> 1) + 2] > 0)
                ignoreOthers = true;

            int rowPt = -1, maxFreeNum = -1, exitDis = INT_MAX;
            for (int j = 1; j < row - 1; j++)
            {
                if (ignoreOthers && j != 1 && j != ((row - 3) >> 1) + 2)
                    continue;

                if (arr[j][0] == '.')
                    continue;

                if (freeNum[j] > maxFreeNum)
                {
                    rowPt = j;
                    maxFreeNum = freeNum[j];
                    exitDis = min(abs((((row - 3) >> 1) + 1) - j), min(j, row - 1 - j));
                }
                else if (freeNum[j] == maxFreeNum)
                {
                    int cntExitDis = min(abs((((row - 3) >> 1) + 1) - j), min(j, row - 1 - j));
                    if (cntExitDis < exitDis)
                    {
                        rowPt = j;
                        exitDis = cntExitDis;
                    }
                }
            }

            // Select seat
            for (int j = 0; j < 5; j++)
            {
                if (prior[j] == 5 && arr[rowPt][prior[j]] == '-')
                {
                    arr[rowPt][prior[j]] = 'a' + i;
                    break;
                }

                if (arr[rowPt][prior[j]] == '-' && arr[rowPt][10 - prior[j]] == '-')
                {
                    // Both available
                    if (leftWeight <= rightWeight)
                    {
                        arr[rowPt][prior[j]] = 'a' + i;
                        leftWeight++;
                        break;
                    }
                    else
                    {
                        arr[rowPt][10 - prior[j]] = 'a' + i;
                        rightWeight++;
                        break;
                    }
                }

                if (arr[rowPt][prior[j]] == '-')
                {
                    arr[rowPt][prior[j]] = 'a' + i;
                    leftWeight++;
                    break;
                }

                if (arr[rowPt][10 - prior[j]] == '-')
                {
                    arr[rowPt][10 - prior[j]] = 'a' + i;
                    rightWeight++;
                    break;
                }
            }

            freeNum[rowPt]--;
        }

        for (int i = 0; i < row; i++)
        {
            printf("%s\n", arr[i]);
        }
    }

    return 0;
}