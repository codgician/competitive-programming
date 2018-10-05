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

#define SIZE 60

bool arr[SIZE][SIZE];
string rowStr, columnStr;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> rowStr >> columnStr)
    {
        int row = rowStr.size();
        int column = columnStr.size();

        int rowZeroNum = 0, columnZeroNum = 0;
        for (auto it = rowStr.begin(); it != rowStr.end(); ++it)
        {
            *it = '0' + ((*it - '0') == (column & 1));
            if (*it == '0')
                rowZeroNum++;
        }
        for (auto it = columnStr.begin(); it != columnStr.end(); ++it)
        {
            *it = '0' + ((*it - '0') == (row & 1));
            if (*it == '0')
                columnZeroNum++;
        }

        if ((rowZeroNum + columnZeroNum) & 1)
        {
            cout << -1 << endl;
            continue;
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                arr[i][j] = 1;
            }
        }

        int cntPt = -1, prevPt = -1;
        while (rowZeroNum > columnZeroNum)
        {
            for (cntPt = cntPt + 1; cntPt < row; cntPt++)
            {
                if (rowStr[cntPt] == '0')
                {
                    if (prevPt == -1)
                    {
                        prevPt = cntPt;
                    }
                    else
                    {
                        arr[prevPt][0] = 0;
                        arr[cntPt][0] = 0;
                        rowStr[prevPt] = '1';
                        rowStr[cntPt] = '1';
                        rowZeroNum -= 2;
                        prevPt = -1;
                        break;
                    }
                }
            }
        }

        cntPt = -1, prevPt = -1;
        while (columnZeroNum > rowZeroNum)
        {
            for (cntPt = cntPt + 1; cntPt < row; cntPt++)
            {
                if (columnStr[cntPt] == '0')
                {
                    if (prevPt == -1)
                    {
                        prevPt = cntPt;
                    }
                    else
                    {
                        arr[0][prevPt] = 0;
                        arr[0][cntPt] = 0;
                        columnStr[prevPt] = '1';
                        columnStr[cntPt] = '1';
                        columnZeroNum -= 2;
                        prevPt = -1;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (rowStr[i] == '0' && columnStr[j] == '0')
                {
                    arr[i][j] = 0;
                    rowStr[i] = '1';
                    columnStr[j] = '1';
                }
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