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
#include <cassert>
using namespace std;

#define SIZE 40

long long int roadArr[SIZE], bufArr[SIZE];

void init(long long int n)
{
    roadArr[0] = 0;
    bufArr[0] = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        roadArr[i] = roadArr[i - 1] + (1ll << i) - 1;
        bufArr[i] = bufArr[i - 1] + ((1ll << (i + 1)) - 3) * (((1ll << (2 * (n - i))) - 1) / 3);

        if (bufArr[i - 1] == LLONG_MAX || bufArr[i] < 0 || bufArr[i] < bufArr[i - 1])
            bufArr[i] = LLONG_MAX;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int n, k;
        cin >> n >> k;

        if (n >= 33)
        {
            cout << "YES " << n - 1 << endl;
            continue;
        }

        init(n);

        bool hasAns = false;
        for (int i = 0; i <= n; i++)
        {
            if (bufArr[i] == LLONG_MAX)
            { 
                cout << "YES " << n - i << endl;
                hasAns = true;
                break;
            }

            if (roadArr[i] + bufArr[i] >= k)
            {
                cout << "YES " << n - i << endl;
                hasAns = true;
                break;
            }

            if (roadArr[i] + bufArr[i] < k && roadArr[i + 1] > k)
            {
                cout << "NO" << endl;
                hasAns = true;
                break;
            }
        }

        if (!hasAns)
            cout << "NO" << endl;
    }

    return 0;
}