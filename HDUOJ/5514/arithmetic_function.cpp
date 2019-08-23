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

#define SIZE 100100

int arr[SIZE], facArr[SIZE];

int getPhi(int n)
{
    int ans = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ans -= ans / i;
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        ans -= ans / n;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int frogNum, stoneNum;
        cin >> frogNum >> stoneNum;

        bool hasCoPrime = false;
        for (int i = 0; i < frogNum; i++)
        {
            cin >> arr[i];
            arr[i] = __gcd(stoneNum, arr[i]);
            if (arr[i] == 1)
                hasCoPrime = true;
        }

        cout << "Case #" << t << ": ";
        if (hasCoPrime)
        {
             cout << ((1ll * stoneNum * (stoneNum - 1)) >> 1) << endl;
             continue;
        }

        sort(arr + 0, arr + frogNum);
        frogNum = unique(arr + 0, arr + frogNum) - arr;

        int facPt = 0;
        for (int i = 2; i * i <= stoneNum; i++)
        {
            if (stoneNum % i > 0)
                continue;

            if (i * i == stoneNum)
            {
                facArr[facPt++] = i;
            }
            else
            {
                facArr[facPt++] = i;
                facArr[facPt++] = stoneNum / i;
            }
        }

        sort(facArr + 0, facArr + facPt);

        long long int ans = 0;
        for (int i = 0; i < facPt; i++)
        {
            for (int j = 0; j < frogNum; j++)
            {
                if (facArr[i] % arr[j] == 0)
                {
                    ans += (1ll * getPhi(stoneNum / facArr[i]) * stoneNum) >> 1;
                    break;
                }
            }
        }

       cout << ans << endl;
    }

    return 0;
}