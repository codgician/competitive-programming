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

const int mod = 998244353;

bool hasChar[26];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    string str;
    cin >> len >> str;

    int charNum = 0;
    memset(hasChar, false, sizeof(hasChar));
    for (auto i : str)
    {
        if (!hasChar[i - 'a'])
        {
            charNum++;
            hasChar[i - 'a'] = true;
        }
    }

    long long int ans = 0;
    if (charNum == 1)
    {
        ans = (1ll * (len + 1) * len) >> 1;
        ans %= mod;
    }
    else
    {
        int leftLen = 0, rightLen = 0;
        for (int i = 0; i < (int)str.size(); i++)
        {
            if (str[i] == str[0])
                leftLen++;
            else
                break;
        }

        for (int i = str.size() - 1; i >= 0; i--)
        {
            if (str[i] == str[str.size() - 1])
                rightLen++;
            else
                break;
        }

        if (str[0] == str[str.size() - 1])
        {
            ans = 1ll * (leftLen + 1) * (rightLen + 1) % mod;
        }
        else
        {
            ans = (leftLen + rightLen + 1) % mod;
        }
    }

    cout << ans << endl;
    return 0;
}