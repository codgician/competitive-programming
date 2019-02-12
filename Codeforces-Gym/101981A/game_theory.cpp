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

bool solve(int num, int k)
{
    if (num == 0)
        return false;
    if (num == 1)
        return true;
    if (num == 2)
    {
        return k > 1;
        if (k == 1)
            return false;
        return true;
    }

    if (k > 1)
        return true;
    if (num & 1)
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num, k;
    while (cin >> num >> k)
    {
        if (solve(num, k))
            cout << "Adrien" << endl;
        else
            cout << "Austin" << endl;
    }

    return 0;
}