#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 1001
using namespace std;

string strArr[SIZE];

typedef struct _Letter {
    unsigned long long int weight;
    int orig;
} letter;

letter letterArr[10];
bool canBeZero[10];
int mapping[10];

bool cmpRule(letter a, letter b)
{
    return a.weight > b.weight;
}

unsigned long long int fastPow(unsigned long long int a, unsigned long long int n)
{
    unsigned long long int ans = 1;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a;
        a = a * a;
        n >>= 1;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    memset(canBeZero, true, sizeof(canBeZero));
    for (int i = 0; i < 10; i++)
    {
        letterArr[i].weight = 0;
        letterArr[i].orig = i;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> strArr[i];
        for (int j = 0; j < strArr[i].length(); j++)
        {
            if (j == 0)
                canBeZero[strArr[i][j] - 'a'] = false;
            letterArr[strArr[i][j] - 'a'].weight += fastPow(10, strArr[i].length() - j - 1);
        }
    }

    sort(letterArr + 0, letterArr + 10, cmpRule);

    int cnt = 1, flag = false;
    for (int i = 0; i < 10; i++)
    {
        if (!flag && canBeZero[letterArr[i].orig])
        {
            flag = true;
            mapping[letterArr[i].orig] = 0;
        }
        else
        {
            mapping[letterArr[i].orig] = cnt;
            cnt++;
        }
    }

    unsigned long long int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < strArr[i].length(); j++)
        {
            sum += fastPow(10, strArr[i].length() - j - 1) * mapping[strArr[i][j] - 'a'];
        }
    }
    cout << sum << endl;
    return 0;
}
