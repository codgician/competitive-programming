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
#include <bitset>
using namespace std;

long long int sqrArr[44730];

void init()
{
    for (int i = 1; i <= 44722; i++)
    {
        sqrArr[i] = i * i;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    string str;
    cin >> str;
    int len = str.length();
    int ans = INT_MAX;
    for (int i = (1 << len) - 1; i >= 0; i--)
    {
        long long int cnt = 0, tmp = 1;
        int cntAns = 0;
        int prevZeroNum = 0;
        for (int j = len - 1; j >= 0; j--)
        {
            if (i & (1 << (len - j - 1)))
            {
                if (str[j] == '0')
                    prevZeroNum++;
                else
                    prevZeroNum = 0;
                cnt += tmp * (str[j] - '0');
                tmp *= 10;
                cntAns++;
            }
        }

        cntAns -= prevZeroNum;

        if (cnt > 0 && binary_search(sqrArr + 1, sqrArr + 44723, cnt))
        {
            ans = min(ans, len - cntAns);
        }
    }
    if (ans == INT_MAX)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}
