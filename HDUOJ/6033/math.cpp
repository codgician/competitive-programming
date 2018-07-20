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

int main()
{
    ios::sync_with_stdio(false);
    int m, casePt = 0;
    while (cin >> m)
    {
        cout << "Case #" << ++casePt << ": ";
        int ans = m * log10(2);
        cout << ans << endl;
    }
    return 0;
}