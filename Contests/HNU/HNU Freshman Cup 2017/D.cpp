#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 99999
#define MAX_VALUE 50000000
using namespace std;

int prime[SIZE];
bool isShuai[50000000];

int shuaiPt = 0, primePt = 0;

bool isPrime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void initPrime(int n)
{
    for (int i = 2; i < sqrt(n); i++)
    {
        if (isPrime(i))
        {
            prime[primePt++] = i;
        }
    }
}

int getPow(int a, int n)
{
    int ans = 1;
    for (int i = 0; i < n; i++)
        ans *= a;
    return ans;
}

int getShuai(int a, int b, int c)
{
    int ans = getPow(a, 2) + getPow(b, 3) + getPow(c, 4);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    if (n < 28)
    {
        cout << 0 << endl;
    }
    else
    {
        memset(isShuai, false ,sizeof(isShuai));
        initPrime(n);

        for (int i = 0; i < primePt; i++)
        {
            if (getShuai(prime[i],0 , 0) > n)
                break;
            for (int j = 0; j < primePt; j++)
            {
                if (getShuai(prime[i], prime[j], 0) > n)
                    break;
                for (int k = 0; k < primePt; k++)
                {
                    int t = getShuai(prime[i], prime[j], prime[k]);
                    if (t > n)
                        break;
                    else
                        isShuai[t - 1] = true;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= n; i++)
        {
            if (isShuai[i])
                ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
