#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int eleNum;
    cin >> eleNum;
    int prev, cnt, next;
    int ans = 0;
    cin >> prev >> cnt;
    for (int i = 2; i < eleNum; i++)
    {
        cin >> next;
        if ((cnt > prev && cnt > next) || (cnt < prev && cnt < next))
            ans++;
        prev = cnt;
        cnt = next;
    }
    cout << ans << endl;
    return 0;
}
