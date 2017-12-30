#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 5001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, 0, sizeof(arr));
    int n, m, maxN = 0;
    cin >> n >> m;
    while (n--)
    {
        int left, right;
        cin >> left >> right;
        left--;
        right--;
        for (int i = left; i <= right; i++)
        {
            arr[i]++;
            maxN = max(maxN, arr[i]);
        }
    }
    if (maxN % m == 0)
    {
        cout << maxN / m << endl;
    }
    else
    {
        cout << maxN / m + 1 << endl;
    }
    return 0;
}
