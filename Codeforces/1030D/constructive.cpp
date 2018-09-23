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

    long long int n, m, k;
    cin >> n >> m >> k;
    long long int xLim = n;

    long long int gcd1 = __gcd(n, k);
    n /= gcd1;
    k /= gcd1;

    long long int gcd2 = __gcd(m, k);
    m /= gcd2;
    k /= gcd2;

    if (k > 2)
    {
        cout << "NO" << endl;
    }
    else
    {
        if (k == 1)
        {
            if ((n << 1) <= xLim)
                n <<= 1;
            else
                m <<= 1;
        }

        cout << "YES" << endl;
        cout << 0 << " " << 0 << endl;
        cout << n << " " << 0 << endl;
        cout << n << " " << m << endl;
    }

    return 0;
}