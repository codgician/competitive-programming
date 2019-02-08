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
#include <cassert>
using namespace std;

#define SIZE 30

int twoPow[SIZE];
int table[SIZE] = {0, 1, 1, 5, 1, 21, 1, 85, 73, 341, 89, 1365, 1, 5461, 4681, 21845, 1, 87381, 1, 349525, 299593, 1398101, 178481, 5592405, 1082401};

void init()
{
    twoPow[0] = 1;
    for (int i = 1; i < SIZE; i++)
        twoPow[i] = twoPow[i - 1] << 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();
    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        int cnt;
        cin >> cnt;

        int pos = lower_bound(twoPow + 0, twoPow + SIZE, cnt + 1) - twoPow, ans;
        if (twoPow[pos] == cnt + 1)
            ans = table[pos - 1];
        else
            ans = twoPow[pos] - 1;
        cout << ans << endl;
    }

    return 0;
}