#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define INF 21252
using namespace std;

int arr[3], mod[3] = {23, 28, 33};
const int modProduct = mod[0] * mod[1] * mod[2];

int extEuclid(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int gcd = extEuclid(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - y * (a / b);
    return gcd;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int cntDate, casePt = 0;
        while (cin >> arr[0] >> arr[1] >> arr[2] >> cntDate)
        {
            if (arr[0] == -1 && arr[1] == -1 && arr[2] == -1 && cntDate == -1)
                break;

            for (int i = 0; i < 3; i++)
            {
                arr[i] %= mod[i];
            }

            int ans = 0;
            for (int i = 0; i < 3; i++)
            {
                int x, y;
                int gcd = extEuclid(modProduct / mod[i], mod[i], x, y);
                int tmp = x / gcd;
                ans += arr[i] * (modProduct / mod[i]) * tmp;
            }
            
            if (ans < 0)
                ans = INF -(-ans) % INF;
            
            if (ans > INF)
                ans %= INF;
            if (ans <= cntDate)
                ans += INF;

            cout << "Case " << ++casePt << ": the next triple peak occurs in " << ans - cntDate << " days." << endl;
        }
    }
    return 0;
}