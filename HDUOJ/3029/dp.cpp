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
#define SIZE 3010
#define MAX_PRIME 3010
using namespace std;

int primeArr[SIZE], factorArr[SIZE], primePt;
double dp[SIZE];
long long int ans[SIZE];

inline void initPrime()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < MAX_PRIME; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (MAX_PRIME - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    initPrime();
    int num, mod;
    while (cin >> num >> mod)
    {
        for (int i = 0; i <= num; i++)
        {
            dp[i] = 0;
            ans[i] = 1;
        }

        for (int i = 0; primeArr[i] <= num; i++)
        {
            double cntLog = log(primeArr[i]);
            for (int j = num; j >= primeArr[i]; j--)
            {
                long long int cntVal = primeArr[i];
                for (int k = 1; cntVal <= j; k++)
                {
                    if (dp[j - cntVal] + k * cntLog > dp[j])
                    {
                        dp[j] = dp[j - cntVal] + k * cntLog;
                        ans[j] = ans[j - cntVal] * cntVal % mod;
                    }
                    cntVal *= primeArr[i];
                }
            }
        }

        cout << ans[num] % mod << endl;
    }
    return 0;
}
