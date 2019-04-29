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

#define SIZE 100010

const long long int mod = 1e9 + 7;

long long int fastPow(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        string str;
        cin >> str;

        long long int expnt = 0;
        long long int tmp = 1;
        for (auto rit = str.rbegin(); rit != str.rend(); ++rit)
        {
            expnt += (*rit - '0') * tmp % (mod - 1);
            tmp *= 10;
            if (tmp >= mod - 1)
                tmp %= mod - 1;
            if (expnt >= mod - 1)
                expnt %= mod - 1;
        }
        expnt = (expnt - 1 + mod - 1) % (mod - 1);
        cout << fastPow(2, expnt) << endl;
    }

    return 0;
}