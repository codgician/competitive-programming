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

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n)
{
    if (a == 0)
    {
        return (n + 1) * (b / c);
    }

    if (a >= c || b >= c)
    {
        long long int tmp = (n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1);
        return (a / c) * tmp + (b / c) * (n + 1) + quasiEuclidean(a % c, b % c, c, n);
    }

    long long int m = (a * n + b) / c;
    return n * m - quasiEuclidean(c, c - b - 1, a, m - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long int a, b, c;
    cin >> a >> b >> c;
    cout << quasiEuclidean(a, b + c % a, b, c / a) << endl;

    return 0;
}