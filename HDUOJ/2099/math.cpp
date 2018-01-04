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
    int a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
            break;
        int tmp = a * 100;
        if (tmp % b != 0)
            tmp += (b - tmp % b);
        cout << setfill('0') << setw(2) << tmp % 100;
        tmp += b;
        while (tmp < (a + 1) * 100)
        {
            cout << " " << setfill('0') << setw(2) << tmp % 100;
            tmp += b;
        }
        cout << endl;
    }
    return 0;
}
