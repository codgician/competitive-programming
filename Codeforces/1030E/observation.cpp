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

int arr[SIZE];
int pfxSum[SIZE];
int evenNum[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    cin >> len;

    pfxSum[0] = 0;
    evenNum[0] = 0;
    for (int i = 1; i <= len; i++)
    {
        unsigned long long int cnt;
        cin >> cnt;
        arr[i] = __builtin_popcountll(cnt);
        pfxSum[i] = pfxSum[i - 1] + arr[i];

        evenNum[i] = evenNum[i - 1];
        if (!(pfxSum[i] & 1))
        {
            evenNum[i] += 1;
        }
    }

    long long int ans = 0;
    for (int i = 1; i <= len; i++)
    {
        int cntSum = 0;
        int maxVal = -1, pt;
        for (pt = i; pt <= len; pt++)
        {
            cntSum += arr[pt];

            if (cntSum >= 120)
            {
                cntSum -= arr[pt];
                break;
            }

            maxVal = max(maxVal, arr[pt]);
            if (!(cntSum & 1))
            {
                if (maxVal <= (cntSum >> 1))
                {
                    ans++;
                }
            }
        }

        if (pt <= len)
        {
            // What we need: { pfxSum[i] - pfxSum[pt - 1] }
            if ((cntSum & 1) == (pfxSum[pt - 1] & 1))
            {
                // even
                ans += evenNum[len] - evenNum[pt - 1];
            }
            else
            {
                // odd
                ans += (len - pt + 1) - (evenNum[len] - evenNum[pt - 1]);
            }
        }
    }

    cout << ans << endl;
    return 0;
}