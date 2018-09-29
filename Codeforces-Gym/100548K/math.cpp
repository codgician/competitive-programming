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

long long int work(long long int a, long long int b)
{
    long long int ans = 1;
    while (b > 0)
    {
        long long int tmp = b;
        ans += a / b;
        b = a % b;
        a = tmp;
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
    for (int t = 1; t <= caseNum; t++)
    {
        long long int a, b;
        cin >> a >> b;
        if (a < b)
            swap(a, b);

        cout << "Case #" << t << ": ";

        if (b == 0)
        {
            if (a == 0)
                cout << 1 << endl;
            else
                cout << 2 << endl;
            continue;
        }

        cout << work(a, b) << endl;
    }

    return 0;
}