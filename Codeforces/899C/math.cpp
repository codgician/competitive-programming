#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int ans[4] = {0, 1, 1, 0}, dArr[4] = {0, 1, 1, 2}, iArr[4] = {2, 1, 2, 1};

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;

    int tmp = n % 4;
    cout << ans[tmp] << endl;
    cout << (n / 4) * 2 + dArr[tmp];

    int i = iArr[tmp];
    bool flag = true;
    while (i <= n)
    {
        cout << " " << i;
        if (flag)
            i += 1;
        else
            i += 3;
        flag = !flag;
    }
    return 0;
}
