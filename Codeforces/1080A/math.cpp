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

    long long int ans = 0;
    ans += (n << 1) / k + ((n << 1) % k != 0);
    ans += (n * 5) / k + ((n * 5) % k != 0);
    ans += (n << 3) / k + ((n << 3) % k != 0);
    cout << ans << endl;

    return 0;
}