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
    int n, m;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
            break;
        if ((n & 1) && (m & 1))
        {
            cout << "What a pity!" << endl;
        }
        else
        {
            cout << "Wonderful!" << endl;
        }
    }
    return 0;
}
