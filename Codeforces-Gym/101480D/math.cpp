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

const long long int mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int len, div;
    while (cin >> len >> div)
    {
        string str;
        cin >> str;

        long long int cntMod = 0, ans = 0;
        for (int i = 0; i < len; i++)
        {
            cntMod = (cntMod * 10 + (str[i] - '0')) % div;
            if (cntMod == 0)
            {
                if (ans == 0)
                    ans = 1;
                else
                {
                    ans <<= 1;
                    ans %= mod;
                }
            }
        }

        if (cntMod != 0)
            cout << 0 << endl;
        else
            cout << ans << endl;
    }

    return 0;
}