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

#define SIZE 300010
#define PRIME_SIZE 5010

int arr[SIZE];

int primeArr[PRIME_SIZE], factorArr[PRIME_SIZE], primePt;
int minNum[PRIME_SIZE];

map<int, int> mp;

void initPrime()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < PRIME_SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (PRIME_SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initPrime();
    int num;
    cin >> num;

    int gcd = 0, maxVal = -1;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i];
        if (gcd != 1)
            gcd = __gcd(gcd, arr[i]);
        maxVal = max(maxVal, arr[i]);
    }

    if (gcd > 1)
    {
        for (int i = 0; i < num; i++)
        {
            arr[i] /= gcd;
        }
    }
    
    mp.clear();
    int ans = INT_MAX;

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; primeArr[j] * primeArr[j] <= arr[i]; j++)
        {
            int cntExp = 0;
            if (arr[i] % primeArr[j] == 0)
            {
                arr[i] /= primeArr[j];
                cntExp++;
                while (arr[i] % primeArr[j] == 0)
                {
                    cntExp++;
                    arr[i] /= primeArr[j];
                }
            }
            if (cntExp > 0)
            {
                if (mp.find(primeArr[j]) == mp.end())
                {
                    mp[primeArr[j]] = num - 1;
                    ans = min(ans, num - 1);
                }
                else
                {
                    mp[primeArr[j]]--;
                    ans = min(ans, mp[primeArr[j]]);
                }

            }
        }

        if (arr[i] > 1)
        {
            if (mp.find(arr[i]) == mp.end())
            {
                mp[arr[i]] = num - 1;
                ans = min(ans, num - 1);
            }
            else
            {
                mp[arr[i]]--;
                ans = min(ans, mp[arr[i]]);
            }
        }
    }

    if (ans == INT_MAX)
        cout << -1 << endl;
    else
        cout << ans << endl;

    return 0;
}