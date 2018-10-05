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

#define SIZE 1000010
#define CHAR_SIZE 26

const int mod = 1e9 + 7;

typedef struct _TrieNode
{
    int wordId;
    int nextArr[CHAR_SIZE];
} TrieNode;

TrieNode trieArr[SIZE];
int triePt, wordPt;

long long int factorialArr[SIZE], invFactorialArr[SIZE];
int bitArr[SIZE];

string strArr[SIZE], s;
int arr[SIZE], arrPt;

int newTrieNode()
{
    trieArr[triePt].wordId = -1;
    for (int i = 0; i < CHAR_SIZE; i++)
        trieArr[triePt].nextArr[i] = -1;
    return triePt++;
}

void insertName(string & str)
{
    int cntPt = 0;
    for (int i = 0; i < (int)str.size(); i++)
    {
        int cnt = str[i] - 'a';
        if (trieArr[cntPt].nextArr[cnt] == -1)
            trieArr[cntPt].nextArr[cnt] = newTrieNode();
        cntPt = trieArr[cntPt].nextArr[cnt];
    }
    trieArr[cntPt].wordId = wordPt++;
}

void findStr(string & str)
{
    int len = str.size(), cntPt = 0;
    arrPt = 0;
    for (int i = 0; i < len; i++)
    {
        int cnt = str[i] - 'a';
        cntPt = trieArr[cntPt].nextArr[cnt];
        if (trieArr[cntPt].wordId != -1)
        {
            arr[arrPt++] = trieArr[cntPt].wordId;
            cntPt = 0;
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

int getPrefixSum(int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

long long int quickPow(long long int a, long long int n)
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
    invFactorialArr[SIZE - 1] = quickPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

long long int getPermu(int n, int m)
{
    if (m > n)
        return 0;
    return factorialArr[n] * invFactorialArr[m] % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initFactorial();
    initInvFactorial();
    int num, k;
    while (cin >> num >> k)
    {
        memset(bitArr, 0, sizeof(bitArr));
        triePt = 0;
        wordPt = 0;
        newTrieNode();
        for (int i = 0; i < num; i++)
            cin >> strArr[i];

        sort(strArr + 0, strArr + num);

        for (int i = 0; i < num; i++)
        {
            add(i + 1, 1);
            insertName(strArr[i]);
        }

        cin >> s;
        findStr(s);

        long long int ans = 1;
        for (int i = 0; i < arrPt; i++)
        {
            int unusedNum = getPrefixSum(arr[i]);
            add(arr[i] + 1, -1);
            ans += unusedNum * getPermu(num - i - 1, num - k) % mod;
            ans %= mod;
        }
        cout << ans << endl;
    }

    return 0;
}