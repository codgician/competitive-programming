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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    cin >> num;

    int prev, cnt;
    cin >> prev;
    int ans = prev;
    for (int i = 1; i < num; i++)
    {
        cin >> cnt;
        if (cnt > prev)
            ans += cnt - prev;
        prev = cnt;
    }
    cout << ans << endl;

    return 0;
}