#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

typedef struct Node {
    long long int a;
    long long int b;
} fraction;

long long int getGcd(long long int a, long long int b)
{
    if (b == 0)
        return a;
    else
        return getGcd(b, a % b);
}

fraction simplify(fraction f)
{
    int gcd = getGcd(f.a, f.b);
    f.a /= gcd;
    f.b /= gcd;
    return f;
}

int main()
{
    ios::sync_with_stdio(false);
    int realNum, fakeNum, throwTimes;
    while (cin >> realNum >> fakeNum >> throwTimes)
    {
        int gcd = getGcd(realNum, fakeNum);
        fraction ans;
        ans.a = realNum / gcd;
        ans.b = ans.a + (fakeNum / gcd) * ((long long int)1 << throwTimes);
        ans = simplify(ans);
        cout << ans.a << "/" << ans.b << endl;
    }
    return 0;
}
