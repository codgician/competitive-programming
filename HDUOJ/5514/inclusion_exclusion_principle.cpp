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
int sgn[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        memset(sgn, 0, sizeof(sgn));
        int frogNum, stoneNum;
        cin >> frogNum >> stoneNum;

        bool hasCoPrime = false;
        for (int i = 0; i < frogNum; i++)
        {
            cin >> arr[i];
            arr[i] = __gcd(arr[i], stoneNum);
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

        for (int i = 0; i < frogNum; i++)
        {
            for (int j = 0; j < facPt; j++)
            {
                if (facArr[j] % arr[i] == 0)
                {
                    sgn[j] = 1;
                }
            }
        }

        long long int ans = 0;
        for (int i = 0; i < facPt; i++)
        {
            if (sgn[i] == 0)
                continue;

            int tmp = stoneNum / facArr[i];
            ans += ((1ll * (tmp - 1) * tmp) >> 1) * facArr[i] * sgn[i];
            for (int j = i + 1; j < facPt; j++)
            {
                if (facArr[j] % facArr[i] == 0)
                    sgn[j] -= sgn[i];
            }
        }

        cout << ans << endl;

    }
    return 0;
}