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
    int plateNum, a, b;
    cin >> plateNum >> a >> b;
    int ans = 0;
    for (int i = 1; i < plateNum; i++)
    {
        int t1 = a / i;
        int t2 = b / (plateNum - i);
        int cnt = min(t1, t2);
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
