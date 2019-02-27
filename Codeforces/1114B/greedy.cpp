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

#define SIZE 200010

int arr[SIZE], dsc[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len, m, k;
    cin >> len >> m >> k;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i];
        dsc[i] = arr[i];
    }
    sort(dsc + 0, dsc + len);
    int num = m * k;
    int edgeVal = dsc[len - num];
    int uppPt = upper_bound(dsc + 0, dsc + len, edgeVal) - dsc;
    while (dsc[uppPt] != edgeVal)
        uppPt--;
    int edgeNum = uppPt - (len - num) + 1;

    long long int ans = 0;
    for (int i = len - 1; i > len - 1 - num; i--)
        ans += dsc[i];
    cout << ans << endl;

    int cntLen = 0, cntNum = 0;
    for (int i = 0; i < len; i++)
    {
        int cntPt = upper_bound(dsc + 0, dsc + len, arr[i]) - dsc;
        while (dsc[cntPt] != arr[i])
            cntPt--;
        if (cntPt >= len - num)
        {
            if (arr[i] == edgeVal)
            {
                if (edgeNum <= 0)
                    cntLen--;
                else
                    edgeNum--;
            }
            cntLen++;
        }

        if (cntLen == m)
        {
            cout << i + 1 << " ";
            cntLen = 0;
            cntNum++;
        }

        if (cntNum == k - 1)
            break;
    }
    cout << endl;

    return 0;
}