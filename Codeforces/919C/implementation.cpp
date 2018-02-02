#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 2001
using namespace std;

bool arr[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, false ,sizeof(arr));
    int row , column, seatNum;
    cin >> row >> column >> seatNum;
    long long int ans = 0;

    if (seatNum == 1)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                char ch;
                cin >> ch;
                if (ch == '.')
                {
                    ans++;
                }
            }
        }
    }
    else
    {
        int cntNum = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                char ch;
                cin >> ch;
                if (ch == '*')
                {
                    arr[i][j] = true;
                    if (cntNum >= seatNum)
                    {
                        ans += cntNum - seatNum + 1;
                    }
                    cntNum = 0;
                }
                else
                {
                    arr[i][j] = false;
                    cntNum++;
                }
            }
            if (cntNum >= seatNum)
            {
                ans += cntNum - seatNum + 1;
            }
            cntNum = 0;
        }

        if (cntNum >= seatNum)
        {
            ans += cntNum - seatNum + 1;
        }
        cntNum = 0;

        for (int j = 0; j < column; j++)
        {
            for (int i = 0; i < row; i++)
            {
                if (arr[i][j])
                {
                    if (cntNum >= seatNum)
                    {
                        ans += cntNum - seatNum + 1;
                    }
                    cntNum = 0;
                }
                else
                {
                    cntNum++;
                }
            }
            if (cntNum >= seatNum)
            {
                ans += cntNum - seatNum + 1;
            }
            cntNum = 0;
        }

        if (cntNum >= seatNum)
        {
            ans += cntNum - seatNum + 1;
        }
        cntNum = 0;
    }
    cout << ans << endl;
    return 0;
}
