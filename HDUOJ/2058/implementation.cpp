#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int n, m;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
            break;
        for (int i = sqrt(2 * m); i > 0; i--)
        {
            int x = 2 * m - i * (i - 1);
            int y = 2 * i;
            if (x > 0 && x % y == 0)
            {
                long long int a = x / y;
                cout << "[" << a << "," << a + i - 1 << "]" << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
