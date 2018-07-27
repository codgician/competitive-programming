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
    int num, base;
    cin >> num >> base;

    int gcd = base;
    for (int i = 0; i < num; i++)
    {
        int cnt;
        cin >> cnt;
        gcd = __gcd(gcd, cnt);
    }

    int ans = base / gcd;
    cout << ans << endl;
    for (int i = 0; i < ans; i++)
    {
        cout << i * gcd;
        if (i < ans - 1)
            cout << " ";
        else
            cout << endl;
    } 
    return 0;
}