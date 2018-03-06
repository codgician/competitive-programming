#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
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

int arr[SIZE][SIZE];
int columnMatch[SIZE];
bool columnTried[SIZE];
int matrixSize;

int cntMin, cntMax;

bool canFind(int rowId)
{
    for (int i = 0; i < matrixSize; i++)
    {
        if (!columnTried[i] && arr[rowId][i] >= cntMin && arr[rowId][i] <= cntMax)
        {
            columnTried[i] = true;
            if (columnMatch[i] == -1 || canFind(columnMatch[i]))
            {
                columnMatch[i] = rowId;
                return true;
            }
        }
    }
    return false;
}

bool hungary()
{
    memset(columnMatch, -1, sizeof(columnMatch));
    for (int i = 0; i < matrixSize; i++)
    {
        memset(columnTried, false, sizeof(columnTried));
        if (!canFind(i))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> matrixSize;
        int maxNum = INT_MIN, minNum = INT_MAX;
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                cin >> arr[i][j];
                maxNum = max(maxNum, arr[i][j]);
                minNum = min(minNum, arr[i][j]);
            }
        }

        int leftPt = 0, rightPt = maxNum - minNum, ans;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;

            bool flag = false;
            for (cntMin = minNum; cntMin + midPt <= maxNum; cntMin++)
            {
                cntMax = cntMin + midPt;
                if (hungary())
                {
                    flag = true;
                    break;
                }
            }

            if (flag)
            {
                ans = midPt;
                rightPt = midPt - 1;
            }
            else
            {
                leftPt = midPt + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
