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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    while (cin >> num)
    {
        int ans = 0;
        for (int i = 0; i < num; i++)
        {
            int cnt;
            cin >> cnt;
            if (cnt != 1)
                ans++;
        }
        cout << ans << endl;
    }

    return 0;
}