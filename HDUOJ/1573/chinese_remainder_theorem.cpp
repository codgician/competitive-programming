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
#define SIZE 20
using namespace std;

int mod[SIZE], cst[SIZE];

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
        int upperLimit, equNum;
        cin >> upperLimit >> equNum;

        for (int i = 0; i < equNum; i++)
        {
            cin >> mod[i];
        }
        for (int i = 0; i < equNum; i++)
        {
            cin >> cst[i];
        }

        bool noSolution = false;
        int modProd = mod[0], prevAns = cst[0];
        for (int i = 1; i < equNum; i++)
        {
            int x, y;
            int a = modProd, b = mod[i], c = cst[i] - prevAns;
            int gcd = extEuclid(a, b, x, y);

            if (c % gcd != 0)
            {
                noSolution = true;
                break;
            }

            int cntAns = c / gcd * x;
            if (cntAns < 0)
                cntAns = (mod[i] / gcd) - (-cntAns) % (mod[i] / gcd);
            else
                cntAns %= mod[i] / gcd;

            prevAns += modProd * cntAns;
            modProd = modProd / gcd * mod[i];
        }

        if (noSolution)
        {
            cout << 0 << endl;
        }
        else
        {
            int ans = 0;
            if (prevAns <= upperLimit)
                ans = (upperLimit - prevAns) / modProd + 1;
            if (ans > 0 && prevAns == 0)
                ans--;
            cout << ans << endl;
        }
    }
    return 0;
}
