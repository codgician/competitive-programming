#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n;
        cin >> n;
        int ans = 0;
        while (n > 0)
        {
            ans += (n & 1);
            n >>= 1;
        }
        cout << ans << endl;
    }
    return 0;
}
