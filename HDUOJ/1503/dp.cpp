#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
#define SIZE 10001
#define IS_SAME 0
#define SELECT_FRONT 1
#define SELECT_BACK -1
using namespace std;

int dp[SIZE][SIZE], st[SIZE][SIZE];
string a, b;

void print(int i, int j)
{
    if (i == 0 && j == 0)
    {
        return;
    }
    else if (st[i][j] == IS_SAME)
    {
        print(i - 1, j - 1);
        cout << a[i - 1];
    }
    else if (st[i][j] == SELECT_FRONT)
    {
        print(i - 1, j);
        cout << a[i - 1];
    }
    else if (st[i][j] == SELECT_BACK)
    {
        print(i, j - 1);
        cout << b[j - 1];
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> a >> b)
    {
        for (int i = 0; i <= a.length(); i++)
        {
            dp[i][0] = 0;
            st[i][0] = SELECT_FRONT;
        }

        for (int j = 0; j <= b.length(); j++)
        {
            dp[0][j] = 0;
            st[0][j] = SELECT_BACK;
        }

        for (int i = 1; i <= a.length(); i++)
        {
            for (int j = 1; j <= b.length(); j++)
            {
                if (a[i - 1] == b[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    st[i][j] = IS_SAME;
                }
                else if (dp[i - 1][j] > dp[i][j - 1])
                {
                    dp[i][j] = dp[i - 1][j];
                    st[i][j] = SELECT_FRONT;
                }
                else
                {
                    dp[i][j] = dp[i][j - 1];
                    st[i][j] = SELECT_BACK;
                }
            }
        }
        if (dp[a.length()][b.length()] == 0)
            cout << a << b;
        else
        {
            print(a.length(), b.length());
        }
        cout << endl;
    }
    return 0;
}
