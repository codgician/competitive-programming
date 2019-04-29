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
using namespace std;

#define SIZE 30010

const int mod = 1e9 + 7;

typedef struct _Query
{
    int id;
    int qLeftPt, qRightPt;
} Query;
Query qArr[SIZE];

int arr[SIZE];
int ansArr[SIZE], posArr[SIZE];
long long int factorialArr[SIZE], invFactorialArr[SIZE];

int cntLeft, cntRight, cntNum;
long long int cntAns;
int numArr[SIZE];

long long int fastPow(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

long long int getInv(int n)
{
    return factorialArr[n - 1] * invFactorialArr[n] % mod;
}

void add(int pos)
{
    cntAns = cntAns * (++cntNum) % mod;
    if (numArr[arr[pos]] > 0)
    {
        cntAns = cntAns * factorialArr[numArr[arr[pos]]] % mod;
        cntAns = cntAns * invFactorialArr[numArr[arr[pos]] + 1] % mod;
    }
    numArr[arr[pos]]++;
}

void remove(int pos)
{
    cntAns = cntAns * getInv(cntNum--) % mod;
    if (numArr[arr[pos]] > 1)
    {
        cntAns = cntAns * factorialArr[numArr[arr[pos]]] % mod;
        cntAns = cntAns * invFactorialArr[numArr[arr[pos]] - 1] % mod;
    }
    numArr[arr[pos]]--;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initFactorial();
    initInvFactorial();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len, qNum;
        cin >> len >> qNum;

        int blockSize = sqrt(len);
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
            posArr[i] = i / blockSize;
        }

        for (int i = 0; i < qNum; i++)
        {
            qArr[i].id = i;
            cin >> qArr[i].qLeftPt >> qArr[i].qRightPt;
            qArr[i].qLeftPt--;
            qArr[i].qRightPt--;
        }

        sort(qArr + 0, qArr + qNum, [](Query & fst, Query & snd) {
            if (posArr[fst.qLeftPt] == posArr[snd.qLeftPt])
                return fst.qRightPt < snd.qRightPt;
            return fst.qLeftPt < snd.qLeftPt;
        });

        memset(numArr, 0, sizeof(numArr));
        cntLeft = 0, cntRight = -1, cntAns = 1, cntNum = 0;
        for (int i = 0; i < qNum; i++)
        {
            while (qArr[i].qRightPt > cntRight)
                add(++cntRight);
            while (qArr[i].qRightPt < cntRight)
                remove(cntRight--);
            while (qArr[i].qLeftPt < cntLeft)
                add(--cntLeft);
            while (qArr[i].qLeftPt > cntLeft)
                remove(cntLeft++);

            ansArr[qArr[i].id] = cntAns;
        }

        for (int i = 0; i < qNum; i++)
        {
            cout << ansArr[i] << endl;
        }
    }

    return 0;
}