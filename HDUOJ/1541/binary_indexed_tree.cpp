#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#define SIZE 32001
using namespace std;

int level[SIZE];
int bit[SIZE];

int getLowbit(int n)
{
    return n & (-n);
}

void add(int x, int val)
{
    while (x < SIZE)
    {
        bit[x] += val;
        x += getLowbit(x);
    }
}

int getRank(int x) // How many stars are lower left
{
    int ans = 0;
    while (x > 0)
    {
        ans += bit[x];
        x -= getLowbit(x);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int starNum;
    while (cin >> starNum)
    {
        memset(bit, 0, sizeof(bit));
        memset(level, 0, sizeof(level));
        for (int i= 0; i < starNum; i++)
        {
            int x, y;
            cin >> x >> y;
            level[getRank(x + 1)]++;  // BIT can't handle 0, need to +1.
            add(x + 1, 1);
        }
        for (int i = 0; i < starNum; i++)
        {
            cout << level[i] << endl;
        }
    }
    return 0;
}
