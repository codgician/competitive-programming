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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int msgNum, initVal, decVal, factor, timeLimit;
    cin >> msgNum >> initVal >> decVal >> factor >> timeLimit;

    int ans = 0;
    if (decVal >= factor)
    {
        ans = msgNum * initVal;
    }
    else
    {
        for (int i = 0; i < msgNum; i++)
        {
            int cnt;
            cin >> cnt;
            ans += (timeLimit - cnt) * (factor - decVal);
        }
        ans += msgNum * initVal;
    }
    cout << ans << endl;
    return 0;
}
