#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 100100
using namespace std;

int arr[SIZE];
long long int dp[SIZE][10];

const int mod = 258280327;

inline int getRoot(int i)
{
    return (i - 1) % 9 + 1;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num, fst, snd;
        cin >> num >> fst >> snd;
        int reqRoot = getRoot(fst + snd), sumRoot = 0;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            arr[i] = getRoot(arr[i]);
            sumRoot += arr[i];
            sumRoot = getRoot(sumRoot);
        }

        for (int i = 0; i <= 9; i++)
        {
            dp[0][i] = 0;
        }
        dp[0][0] = 1;
        dp[0][arr[0]] = 1;

        for (int i = 1; i < num; i++)
        {
            dp[i][0] = 1;
            for (int j = 1; j <= 9; j++)
            {
                int prevRoot = getRoot(j + 9 - arr[i]);
                dp[i][j] = dp[i - 1][j] + dp[i - 1][prevRoot];

                if (prevRoot == 9)
                    dp[i][j]++;

                if (dp[i][j] >= mod)
                    dp[i][j] %= mod;
            }
        }

        int ans = 0;
        if (reqRoot == sumRoot)
        {
            ans = dp[num - 1][fst];
            if (sumRoot == snd)
                ans++;
        }
        else
        {
            if (sumRoot == fst)
                ans++;
            if (sumRoot == snd)
                ans++;
        }

        if (ans >= mod)
            ans %= mod;
        cout << ans << endl;
    }
    return 0;
}