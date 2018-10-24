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

long long int mod[SIZE], cst[SIZE];

long long int extEuclidean(long long int a, long long int b, long long int &x, long long int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long int gcd = extEuclidean(b, a % b, x, y);
    long long int tmp = x;
    x = y;
    y = tmp - y * (a / b);

    return gcd;
}

int main()
{
    ios::sync_with_stdio(false);
    int equNum;
    long long int delta;
    while (cin >> equNum >> delta)
    {
        if (equNum == 0 && delta == 0)
            break;

        for (int i = 0; i < equNum; i++)
        {
            cin >> mod[i];
            cst[i] = mod[i] - delta;
        }

        long long int modProd = mod[0], prevAns = cst[0];
        for (int i = 1; i < equNum; i++)
        {
            long long int x, y;
            long long int a = modProd, b = mod[i], c = cst[i] - prevAns;
            long long int gcd = extEuclidean(a, b, x, y);

            long long int cntAns = c / gcd * x;
            if (cntAns < 0)
                cntAns = (mod[i] / gcd) - (-cntAns) % (mod[i] / gcd);
            else
                cntAns %= mod[i] / gcd;

            prevAns += modProd * cntAns;
            modProd = modProd / gcd * mod[i];
        }

        cout << prevAns % modProd << endl;
    }
    return 0;
}