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
    int ans = (n / 10) * 10;
    if (n - ans >= 5)
        ans += 10;
    cout << ans << endl;
    return 0;
}
