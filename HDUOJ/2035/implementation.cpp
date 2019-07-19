#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int getPow(int a, int b)
{
    int ans = 1;
    for (int i = 0; i < b; i++)
    {
        ans *= a;
        ans %= 1000;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
            break;

        a %= 1000;
        cout << getPow(a, b) << endl;
    }
    return 0;
}
