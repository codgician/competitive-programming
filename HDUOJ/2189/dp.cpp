#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define INF 999999
#define SIZE 151
using namespace std;

bool isPrime[SIZE];
int dp[SIZE];

void initPrime()
{
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = false;
    for (int i = 2; i <= sqrt(SIZE); i++)
    {
        for (int j = 2; j * i < SIZE; j++)
        {
            isPrime[i * j - 1] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    initPrime();
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int n;
        cin >> n;

        dp[0] = 1;
        for (int i = 1; i <= n; i++)
            dp[i] = 0;
        for (int i = 2; i <= n; i++)
        {
            if (!isPrime[i - 1])
                continue;
            for (int j = i; j <= n; j++)
            {
                dp[j] += dp[j - i];
            }
        }

        cout << dp[n] << endl;
    }
    return 0;
}
