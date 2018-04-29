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
#include <stack>
#include <functional>
#include <iterator>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len;
        cin >> len;

        bool ans = true;
        int prev, cnt, pt = 1;
        cin >> prev;
        while (pt < len)
        {
            cin >> cnt;
            if (cnt <= prev)
            {
                prev = cnt;
                break;
            }
            prev = cnt;
            pt++;
        }

        if (pt == 1 || pt == len)
        {
            ans = false;
        }

        pt++;

        while (pt < len)
        {
            cin >> cnt;
            if (cnt >= prev)
            {
                ans = false;
            }
            prev = cnt;
            pt++;
        }

        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}