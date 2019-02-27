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

int req[3], num[3];

bool check()
{
    if (req[0] > num[0])
        return false;
    num[0] -= req[0];
    req[2] -= num[2];

    if (req[1] > num[0] + num[1])
        return false;
    if (req[2] > num[0] + num[1] - req[1])
        return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 3; i++)
        cin >> req[i];
    for (int i = 0; i < 3; i++)
        cin >> num[i];

    if (check())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}