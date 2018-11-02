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
#include <cassert>
using namespace std;

#define SIZE 100010

int arr[SIZE];
int row, column;
bool hasDone, chosen[SIZE];

int & getArr(int * arr, int i, int j)
{
    return *(arr + i * column + j);
}

bool chkAdj(int stdVal, int chkVal)
{
    int stdRow = (stdVal - 1) / column, stdColumn = (stdVal - 1) % column;
    if (stdRow > 0 && stdVal - column == chkVal)
        return false;
    if (stdRow < row - 1 && stdVal + column == chkVal)
        return false;
    if (stdColumn > 0 && stdVal - 1 == chkVal)
        return false;
    if (stdRow < column - 1 && stdVal + 1 == chkVal)
        return false;
    return true;
}

void dfs(int pos)
{
    if (pos == row * column)
    {
        hasDone = true;
        return;
    }

    int cntRow = pos / column, cntColumn = pos % column;
    for (int i = 1; i <= row * column; i++)
    {
        if (chosen[i])
            continue;

        if (cntRow > 0 && getArr(arr, cntRow - 1, cntColumn) != 0 && (!chkAdj(i, getArr(arr, cntRow - 1, cntColumn)) || !chkAdj(getArr(arr, cntRow - 1, cntColumn), i)))
            continue;
        if (cntColumn > 0 && getArr(arr, cntRow, cntColumn - 1) != 0 && (!chkAdj(i, getArr(arr, cntRow, cntColumn - 1)) || !chkAdj(getArr(arr, cntRow, cntColumn - 1), i)))
            continue;

        arr[pos] = i;
        chosen[i] = true;
        dfs(pos + 1);
        if (hasDone)
            return;
        arr[pos] = 0;
        chosen[i] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> row >> column;

    if (row <= 4 && column <= 4)
    {
        memset(arr, 0, sizeof(arr));
        memset(chosen, false, sizeof(chosen));
        hasDone = false;
        dfs(0);

        if (hasDone)
        {
            cout << "YES" << endl;
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    cout << getArr(arr, i, j) << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "NO" << endl;
        }
        return 0;
    }

    cout << "YES" << endl;
    if (row > column)
    {
        for (int j = 0; j < column; j++)
        {
            int fstStart = j + 1, sndStart = j + column + 1;
            int lim = fstStart + column * (row - 1) + 1;
            if ((j & 1) == 0)
                swap(fstStart, sndStart);

            int cntPt = 0;
            while (fstStart < lim)
            {
                getArr(arr, cntPt++ , j) = fstStart;
                fstStart += (column << 1);
            }

            while (sndStart < lim)
            {
                getArr(arr, cntPt++ , j) = sndStart;
                sndStart += (column << 1);
            }
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << getArr(arr, i, j) << " ";
            }
            cout << endl;
        }
    }
    else
    {
        for (int i = 0; i < row; i++)
        {
            int fstStart = i * column + 1, sndStart = i * column + 2;
            int lim = fstStart + column;
            if ((i & 1) == 0)
                swap(fstStart, sndStart);

            while (fstStart < lim)
            {
                cout << fstStart << " ";
                fstStart += 2;
            }

            while (sndStart < lim)
            {
                cout << sndStart << " ";
                sndStart += 2;
            }

            cout << endl;
        }
    }

    return 0;
}