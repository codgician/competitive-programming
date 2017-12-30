#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 100001
using namespace std;

long long int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    long long minVal = LONG_LONG_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        minVal = min(minVal, arr[i]);
    }
    long long int ans = LONG_LONG_MAX, prev = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == minVal)
        {
            if (prev != -1)
            {
                ans = min(ans, i - prev);
            }
            prev = i;
        }
    }
    cout << ans << endl;
    return 0;
}
