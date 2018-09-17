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

const long double pi = acos(-1.0);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long double rad;
    while (cin >> rad)
    {
    	long double ans1 = pi * rad * rad;
    	long double ans2 = rad * rad * 2;

    	cout << fixed << setprecision(6) << ans1 << endl << ans2 << endl;
    }

    return 0;
}