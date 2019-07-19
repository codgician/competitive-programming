#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define SIZE 70000
using namespace std;

bool isPrime(long long int n)
{
    if (n <= 1)
        return false;
    for (long long int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    while (cin >> caseNum)
    {
        int ans = 0;
        for (int t = 0; t < caseNum; t++)
        {
            long long int n;
            cin >> n;
            if (isPrime(n))
                ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
