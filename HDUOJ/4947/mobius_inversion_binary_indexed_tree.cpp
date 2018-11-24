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
#include <cassert>
using namespace std;

#define SIZE 200010

int primeArr[SIZE], minFacArr[SIZE], mu[SIZE], primePt;

long long int bitArr[SIZE];
vector<int> facArr;

void initMu()
{
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    mu[1] = 1;
    for (int i = 2; i < SIZE; i++)
    {
        if (minFacArr[i] == 0)
        {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
            mu[i] = -1;
        }

        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++)
        {
            minFacArr[i * primeArr[j]] = primeArr[j];
            if (minFacArr[i] == primeArr[j])
                mu[i * primeArr[j]] = 0;
            else
                mu[i * primeArr[j]] = -mu[i];
        }
    }
}

int getLowbit(int n)
{
    return n & (-n);
}

void add(int pos, int val)
{
    for (int i = pos; i < SIZE; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

long long int getPrefixSum(int pos)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initMu();

    int len, qNum, casePt = 0;
    while (cin >> len >> qNum)
    {
        if (len == 0 && qNum == 0)
            break;
        
        cout << "Case #" << ++casePt << ":" << endl;
        memset(bitArr, 0, sizeof(bitArr));
        while (qNum--)
        {
            int opr;
            cin >> opr;
            if (opr == 1)
            {
                int n, d, v;
                cin >> n >> d >> v;
                if (n % d != 0)
                    continue;

                facArr.clear();
                n /= d;
                for (int i = 1; i * i <= n; i++)
                {
                    if (n % i == 0)
                    {
                        facArr.push_back(i);
                        if (i * i != n)
                            facArr.push_back(n / i);
                    }
                }

                for (auto i : facArr)
                {
                    if (mu[i] == 0)
                        continue;
                    add(i * d, mu[i] * v);
                }
            }
            else if (opr == 2)
            {
                int x;
                cin >> x;

                long long int ans = 0;
                for (int i = 1, j; i <= x; i = j + 1)
                {
                    if (x / i == 0)
                        break;
                    j = x / (x / i);
                    ans += (x / i) * (getPrefixSum(j) - getPrefixSum(i - 1));
                }
                cout << ans << endl;
            }
        }
    }

    return 0;
}