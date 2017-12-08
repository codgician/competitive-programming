#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 21
using namespace std;

int isPrime[SIZE * 2], ringArr[SIZE];
bool isUsed[SIZE];
int ringPt, n;

void initPrime()
{
    memset(isPrime, false, sizeof(isPrime));
    isPrime[1] = true;
    isPrime[2] = true;
    isPrime[4] = true;
    isPrime[6] = true;
    isPrime[10] = true;
    isPrime[12] = true;
    isPrime[16] = true;
    isPrime[18] = true;
    isPrime[22] = true;
    isPrime[28] = true;
    isPrime[30] = true;
    isPrime[36] = true;
    isPrime[40] = true;
}

void initRing()
{
    memset(isUsed, false, sizeof(isUsed));
    ringPt = 0;
}

void output()
{
    for (int i = 0; i < ringPt; i++)
    {
        cout << ringArr[i];
        if (i < ringPt - 1)
            cout << " ";
        else
            cout << endl;
    }
}

void dfs(int cnt)
{
    /*
    cout << "cnt = " << cnt << " ringPt = " << ringPt << endl;
    output();
    */

    isUsed[cnt - 1] = true;
    ringArr[ringPt] = cnt;
    ringPt++;

    if (ringPt == n)
    {
        if (isPrime[cnt])
        {
            output();
        }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (!isUsed[i - 1] && isPrime[i + cnt - 1])
                dfs(i);
        }
    }

    isUsed[cnt - 1] = false;
    ringPt--;

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    initPrime();
    int caseNum = 1;
    while (cin >> n)
    {
        initRing();
        cout << "Case " << caseNum << ":" << endl;
        dfs(1);
        caseNum++;
        cout << endl;
    }
    return 0;
}
