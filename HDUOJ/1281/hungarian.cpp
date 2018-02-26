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
#define SIZE 101
using namespace std;

bool arr[SIZE][SIZE], hasTried[SIZE];
int columnMatch[SIZE];
int row, column;

bool canFind(int rowId)
{
    for (int i = 0; i < column; i++)
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
    for (int i = 0; i < row; i++)
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
    int avaNum, caseId = 1;
    while (cin >> row >> column >> avaNum)
    {
        memset(arr, false, sizeof(arr));
        for (int i = 0; i < avaNum; i++)
        {
            int x, y;
            cin >> x >> y;
            arr[--x][--y] = true;
        }

        int chessNum = hungarian();
        int importantNum = 0;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (arr[i][j])
                {
                    arr[i][j] = false;
                    int cntNum = hungarian();
                    if (cntNum < chessNum)
                        importantNum++;
                    arr[i][j] = true;
                }
            }
        }
        cout << "Board " << caseId++ << " have " << importantNum << " important blanks for " << chessNum << " chessmen." << endl;
    }
    return 0;
}
