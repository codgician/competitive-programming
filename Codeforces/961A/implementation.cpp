#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 1010
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, 0, sizeof(arr));
    int len, num;
    cin >> len >> num;
    for (int i = 0; i < num; i++)
    {
        int cnt;
        cin >> cnt;
        cnt--;
        arr[cnt]++;
    }

    int ans = INT_MAX;
    for (int i = 0; i < len; i++)
    {
        ans = min(ans, arr[i]);
    }

    cout << ans << endl;
    return 0;
}
