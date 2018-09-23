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

int n, d;

bool check(int x, int y)
{
    int y1 = -x + d;
    if (y1 > y)
        return false;

    int y2 = x - d;
    if (y2 > y)
        return false;

    int y3 = x + d;
    if (y > y3)
        return false;

    int y4 = -x + 2 * n - d;
    if (y > y4)
        return false;

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> d;
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        int x, y;
        cin >> x >> y;

        if (check(x, y))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}