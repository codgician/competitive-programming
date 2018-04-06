#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 101
using namespace std;

int changeZero[4];

int main()
{
    ios::sync_with_stdio(false);
    memset(changeZero, 0, sizeof(changeZero));
    int n;
    cin >> n;
    for (int k = 0; k < 4; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char ch;
                cin >> ch;
                if ((((i + j) & 1) && ch == '0') || (!((i + j) & 1) && ch == '1'))
                    changeZero[k]++;
            }
        }
    }

    sort(changeZero + 0, changeZero + 4);

    int ans = changeZero[0] + changeZero[1] + ((n * n) << 1) - changeZero[2] - changeZero[3];
    cout << ans << endl;
    return 0;
}
