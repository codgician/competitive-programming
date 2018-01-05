#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, 0, sizeof(arr));
    int n, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int startPt = 0; startPt < n - i; startPt++)
        {
            for (int j = startPt; j <= startPt + i; j++)
            {
                arr[j]++;
                ans = max(ans, arr[j]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
