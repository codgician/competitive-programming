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
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int n, a, b;
        cin >> n >> a >> b;
        cout << "Case #" << t << ": ";

        if ((n / __gcd(a, b)) & 1)
            cout << "Yuwgna" << endl;
        else
            cout << "Iaka" << endl;
    }

    return 0;
}