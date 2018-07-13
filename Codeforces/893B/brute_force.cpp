#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int ans[9] = {1, 6, 28, 120, 496, 2016, 8128, 32640, 130816};

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 8; i >= 0; i--)
    {
        if (n % ans[i] == 0)
        {
            cout << ans[i] << endl;
            break;
        }
    }
    return 0;
}