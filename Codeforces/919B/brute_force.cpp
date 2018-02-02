#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

int getBitSum(long long int k)
{
    int ans = 0;
    while (k)
    {
        ans += k % 10;
        k /= 10;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int k;
    cin >> k;

    int cnt = 19;
    k--;
    while (k)
    {
        cnt += 9;
        if (getBitSum(cnt) == 10)
            k--;
    }
    cout << cnt << endl;
    return 0;
}
