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
#include <bitset>
#include <cassert>
using namespace std;

#define SIZE 100010

long long int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    long long int indLim, totLim;
    cin >> len >> indLim >> totLim;

    long long int sum = 0;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i];
        sum += arr[i];
    }
    sort(arr + 0, arr + len);

    long double ans = ((long double)sum + min(totLim, indLim * len)) / len;

    for (int i = 0; i < len; i++)
    {
        int cntLen = len - i - 1;
        long long int cntTotLim = totLim - i - 1;
        sum -= arr[i];
        ans = max(ans, ((long double)sum + min(cntTotLim, indLim * cntLen)) / cntLen);
        if (cntTotLim == 0)
            break;
    }

    cout << fixed << setprecision(12) << ans << endl;
    return 0;
}