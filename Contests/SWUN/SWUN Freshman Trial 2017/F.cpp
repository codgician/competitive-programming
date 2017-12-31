#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int arr[13][13] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 3, 2, 2, 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 3, 2, 2, 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 3, 2, 2, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int main()
{
    ios::sync_with_stdio(false);
    int shotNum;
    while (cin >> shotNum)
    {
        if (shotNum == 0)
            break;
        int ans = 0;
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                char ch;
                cin >> ch;
                if (ch == '#')
                    ans += arr[i][j];
            }
        }
        cout << fixed << setprecision(2) << ans / (double)shotNum << endl;
    }
    return 0;
}
