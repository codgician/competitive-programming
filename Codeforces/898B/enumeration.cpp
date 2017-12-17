#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n, a, b;
    bool hasSwapped = false;
    cin >> n >> a >> b;
    if (a < b)
    {
        swap(a, b);
        hasSwapped = true;
    }
    int aAns = -1, bAns = -1;
    for (int x = 0; x <= n / a; x++)
    {
        if ((n - a * x) % b == 0)
        {
            aAns = x;
            bAns = (n - a * x) / b;
            break;
        }
    }

    if (aAns != -1 && bAns != -1)
    {
        cout << "YES" << endl;
        if (hasSwapped)
            cout << bAns << " " << aAns << endl;
        else
            cout << aAns << " " << bAns << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}
