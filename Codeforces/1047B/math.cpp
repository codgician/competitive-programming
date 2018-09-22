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
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    cin >> num;

    long long int ans = LLONG_MIN;
    for (int i = 0; i < num; i++)
    {
        long long int x, y;
        cin >> x >> y;
        ans = max(ans, x + y);
    }

    cout << ans << endl;

    return 0;
}