#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 5
#define MATCH_SIZE 25
using namespace std;

typedef struct _Node
{
    int x, y;
} Node;

bool isBlock[SIZE][SIZE], arr[MATCH_SIZE][MATCH_SIZE], hasTried[MATCH_SIZE];
Node newLoc[SIZE][SIZE];
int columnMatch[MATCH_SIZE];
int matrixSize, cntRow = 0, cntColumn = 0;

bool canFind(int rowId)
{
    for (int i = 0; i < cntColumn; i++)
    {
        if (arr[rowId][i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (columnMatch[i] == -1 || canFind(columnMatch[i]))
            {
                columnMatch[i] = rowId;
                return true;
            }
        }
    }
    return false;
}

int hungarian()
{
    memset(columnMatch, -1, sizeof(columnMatch));
    int ans = 0;
    for (int i = 0; i < cntRow; i++)
    {
        memset(hasTried, false, sizeof(hasTried));
        if (canFind(i))
            ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> matrixSize)
    {
        if (matrixSize == 0)
            break;

        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                char ch;
                cin >> ch;
                if (ch == 'X')
                    isBlock[i][j] = true;
                else
                    isBlock[i][j] = false;
            }
        }

        cntRow = -1, cntColumn = -1;
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                if (!isBlock[i][j])
                {
                    if (j == 0 || isBlock[i][j - 1])
                        cntRow++;
                    newLoc[i][j].x = cntRow;
                }
                if (!isBlock[j][i])
                {
                    if (j == 0 || isBlock[j - 1][i])
                        cntColumn++;
                    newLoc[j][i].y = cntColumn;
                }
            }
        }
        cntRow++;
        cntColumn++;

        memset(arr, false, sizeof(arr));
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                if (!isBlock[i][j])
                {
                    arr[newLoc[i][j].x][newLoc[i][j].y] = true;
                }
            }
        }

        int ans = hungarian();
        cout << ans << endl;
    }
    return 0;
}
