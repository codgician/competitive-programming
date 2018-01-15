#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int tabNum, pos, left, right;
    cin >> tabNum >> pos >> left >> right;
    int ans;

    if (left == 1 && right == tabNum)
    {
        ans = 0;
    }
    else if (left == 1)
    {
        ans = abs(pos - right) + 1;
    }
    else if (right == tabNum)
    {
        ans = abs(pos - left) + 1;
    }
    else
    {
        ans = min(abs(pos - left), abs(pos - right)) + (right - left) + 2;
    }

    cout << ans << endl;
    return 0;
}
