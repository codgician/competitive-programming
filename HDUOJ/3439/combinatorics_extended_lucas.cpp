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
#define EQU_SIZE 100010
#define SIZE 100010
using namespace std;

long long int primeArr[SIZE], factorArr[SIZE];
int primePt;

long long int modArr[EQU_SIZE], cstArr[EQU_SIZE];
int equNum;

inline void initPrime()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

inline long long int fastPow(long long int a, long long int n, long long int mod)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

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

inline long long int crt(long long int mod)
{
    long long int modProduct = modArr[0], ans = 0;
    for (int i = 1; i < equNum; i++)
    {
        modProduct *= modArr[i];
    }

    for (int i = 0; i < equNum; i++)
    {
        long long int x, y;
        long long int gcd = extEuclidean(modProduct / modArr[i], modArr[i], x, y);
        long long int tmp = x / gcd;
        ans += cstArr[i] * (modProduct / modArr[i]) * tmp;
    }

    if (ans < 0)
        ans = mod -(-ans) % mod;
    else
        ans %= mod;
    return ans;
}

inline long long int getInverse(long long int a, long long int mod)
{
    long long int x, y;
    extEuclidean(a, mod, x, y);
    return (x + mod) % mod;
}

// Solve n! % (prime ^ t)
long long int calc(long long int n, long long int prime, long long int mod)
{
    if (n == 0)
        return 1;
    long long int ans = 1;
    for (int i = 1; i <= mod; i++)
    {
        if (i % prime != 0)
        {
            ans = ans * i % mod;
        }
    }
    ans = fastPow(ans, n / mod, mod);
    for (int i = n / mod * mod + 1; i <= n; i++)
    {
        if (i % prime != 0)
        {
            ans = ans * i % mod;
        }
    }
    return ans * calc(n / prime, prime, mod) % mod;
}

inline long long int multiLucas(long long int n, long long int m, long long int prime, long long int mod)
{
    long long int pNum = 0;
    for (int i = n; i > 0; i /= prime)
        pNum += i / prime;
    for (int i = m; i > 0; i /= prime)
        pNum -= i / prime;
    for (int i = n - m; i > 0; i /= prime)
        pNum -= i / prime;

    return fastPow(prime, pNum, mod) * calc(n, prime, mod) % mod * getInverse(calc(m, prime, mod), mod) % mod * getInverse(calc(n - m, prime, mod), mod) % mod;
}

inline long long int extLucas(long long int n, long long int m, long long int mod)
{
    equNum = 0;
    long long int modTmp = mod;
    for (int i = 0; i < primePt && primeArr[i] <= modTmp; i++)
    {
        if (modTmp % primeArr[i] == 0)
        {
            modArr[equNum] = primeArr[i];
            modTmp /= primeArr[i];
            while (modTmp % primeArr[i] == 0)
            {
                modArr[equNum] *= primeArr[i];
                modTmp /= primeArr[i];
            }

            cstArr[equNum] = multiLucas(n, m, primeArr[i], modArr[equNum]);
            equNum++;
        }
    }

    return crt(mod);
}

inline long long int getDearrange(long long int num, long long int mod)
{
    if (num == 0)
        return 1;

    long long int ans = 0;
    num %= mod << 1;
    if (num == 0)
        num = mod << 1;

    for (int i = 2; i <= num; i++)
    {
        ans *= i;
        if (i & 1)
            ans--;
        else
            ans++;
        ans = (ans + mod) % mod;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    initPrime();
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        long long int n, m, k;
        cin >> n >> k >> m;

        long long int ans = extLucas(n, k, m);
        ans = ans * getDearrange(n - k, m) % m;
        cout << "Case " << t << ": " << ans << endl;
    }
    return 0;
}
