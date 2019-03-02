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

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    cin >> len;
    int maxVal = -1;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i];
        maxVal = max(maxVal, arr[i]);
    }

    int ans = 0, cnt = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == maxVal)
            cnt++;
        else
        {
            ans = max(ans, cnt);
            cnt = 0;
        }
    }
    ans = max(ans, cnt);

    cout << ans << endl;

    return 0;
}