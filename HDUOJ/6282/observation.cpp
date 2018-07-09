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
    string a, b;
    while (cin >> a >> b)
    {
        a += 'c';
        b += 'c';
        int aLen = a.size(), bLen = b.size();

        bool ans = true;
        int aPt = 0, bPt = 0;
        int num[2][2];

        while (aPt < aLen && bPt < bLen)
        {
            memset(num, 0, sizeof(num));
            while (aPt < aLen && a[aPt] != 'c')
            {
                num[0][a[aPt] - 'a']++;
                aPt++;
            }
            while (bPt < bLen && b[bPt] != 'c')
            {
                num[1][b[bPt] - 'a']++;
                bPt++;
            }

            for (int i = 0; i < 2; i++)
            {
                if ((num[0][i] & 1) != (num[1][i] & 1))
                {
                    ans = false;
                    break;
                }
            }
            aPt++;
            bPt++;

            if ((aPt == aLen) != (bPt == bLen))
                ans = false;
            
            if (!ans)
                break;
        }

        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
