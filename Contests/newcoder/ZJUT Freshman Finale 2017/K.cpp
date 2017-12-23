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
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int money, x, y;
        cin >> money >> x >> y;
        if (money < x)
        {
            cout << 0 << endl;
        }
        else
        {
            int ans1 = 3 * (money / x) + (money % x) / y;
            int ans2 = 3 + (money - x) / y;
            cout << max(ans1, ans2) << endl;
        }
    }
    return 0;
}
