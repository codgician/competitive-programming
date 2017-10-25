// Let's get gay with girls!
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

int getFactorial(long long int n)
{
    if (n == 0)
        return 1;
    else if (n >= 2009)
        return 0;
    int ans = n;
    for (long long int i = 2; i < n; i++)
    {
        ans *= i % 2009;
        ans %= 2009;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int n;
    while (cin >> n)
    {
        cout << getFactorial(n) << endl;
    }
    return 0;
}
