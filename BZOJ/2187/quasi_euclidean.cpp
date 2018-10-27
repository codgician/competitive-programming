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

void simplify(int & a, int & b)
{
    int gcd = __gcd(a, b);
    a /= gcd;
    b /= gcd;
}

pair<int, int> solve(int a, int b, int c, int d)
{
    int left = a / b + 1, right = c / d - (c % d == 0);
    if (left <= right)
        return make_pair(left, 1);
    if (a == 0)
        return make_pair(1, d / c + 1);
    if (a <= b && c <= d)
    {
        pair<int, int> ans = solve(d, c, b, a);
        swap(ans.first, ans.second);
        simplify(ans.first, ans.second);
        return ans;
    }

    int t = a / b;
    pair<int, int> ans = solve(a % b, b, c - t * d, d);
    ans.first += ans.second * t;
    simplify(ans.first, ans.second);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, b, c, d;
    while (cin >> a >> b >> c >> d)
    {
        pair<int, int> ans = solve(a, b, c, d);
        cout << ans.first << "/" << ans.second << endl;
    }

    return 0;
}