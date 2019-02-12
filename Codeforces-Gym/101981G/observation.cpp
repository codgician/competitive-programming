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

const int mod = 1e9 + 7;
const int inv24 = 41666667;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;
        long long int ans = 1ll * num * (num + 1) % mod * (num + 2) % mod * (num + 3) % mod * inv24 % mod;
        cout << ans << '\n';
    }

    return 0;
}