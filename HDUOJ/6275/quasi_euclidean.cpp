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

const long long int lim = 3e7; 

long long int quasiEuclidean(long long int a, long long int b, long long int c, long long int n)
{
    if (a == 0)
        return (n + 1) & (b / c) & 1;

    if (a >= c || b >= c)
    {
        long long int tmp = ((n & 1) ? ((n + 1) >> 1) & n : (n >> 1) & (n + 1)) & 1;
        return (quasiEuclidean(a % c, b % c, c, n) ^ ((a / c) & tmp) ^ ((n + 1) & (b / c))) & 1;
    }
    
    long long int m = (a * n + b) / c;
    return ((m & n) ^ quasiEuclidean(c, c - b - 1, a, m - 1)) & 1;
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        long long int n;
        scanf("%lld", &n);

        long long int ans = 0;
        for (long long int i = 1; i <= min(n, lim); i++)
            ans ^= n % i;
        for (long long int leftPt = lim + 1, rightPt; leftPt <= n; leftPt = rightPt + 1)
        {
            rightPt = n / (n / leftPt);

            long long int k = 1, cntAns = 0;
            long long int upperMax = n / leftPt * (rightPt - leftPt) + n % rightPt;
            for (int i = 0; k <= upperMax; i++)
            {
                cntAns += quasiEuclidean(n / leftPt, n % rightPt, k, rightPt - leftPt) << i;
                k <<= 1;
            }
            ans ^= cntAns;
        }

        printf("%lld\n", ans);
    }

    return 0;
}