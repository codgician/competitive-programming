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

#define SIZE 100010

const int mod = 1e9 + 7;

long long int twoPow[SIZE];

void initTwoPow()
{
    twoPow[0] = 1;
    for (int i = 1; i < SIZE; i++)
    {
        twoPow[i] = (twoPow[i - 1] << 1) % mod;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initTwoPow();
    int vertexNum;
    string str;
    while (cin >> vertexNum >> str)
    {
        reverse(str.begin(), str.end());
        long long int ans = 1, cnt = 0;

        for (int i = vertexNum - 1; i >= 0; i--)
        {
            if (i >= (int)str.size() || str[i] == '0')
            {
                cnt++;
            }
            else
            {
                ans = ans * (twoPow[cnt] - 1 + mod) % mod * twoPow[i] % mod;
            }
        }

        cout << ans << endl;
    }

    return 0;
}