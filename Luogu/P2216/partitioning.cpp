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

    long long int n, k;
    cin >> n >> k;

    long long int ans = n * k;
    for (long long int i = 1, j; i <= n; i = j + 1)
    {
        if (k / i == 0)
            break;
        j = min(n, k / (k / i));
        ans -= (k / i) * (((i + j) & 1) ? ((j - i + 1) >> 1) * (i + j) : ((i + j) >> 1) * (j - i + 1));
    }
    cout << ans << endl;

    return 0;
}