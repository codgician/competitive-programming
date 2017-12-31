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
    int n;
    cin >> n;
    if (n == 1)
        cout << 1 << endl;
    else
    {
        cout << 1;
        int i = 1;
        while (true)
        {
            if (2 * i + 1 <= n)
            {
                cout << " " << 2 * i + 1 << " " << 2 * i;
                if (2 * i + 1 == n)
                    break;
            }
            else
            {
                cout << " " << 2 * i;
                break;
            }
            i++;
        }
        cout << endl;
    }
    return 0;
}
