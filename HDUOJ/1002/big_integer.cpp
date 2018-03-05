#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#define SIZE 1002
using namespace std;

int a[SIZE], b[SIZE], ans[SIZE];
int aLength, bLength, ansLength, t, caseNum;

void print()
{
    cout << "Case " << t << ":" << endl;
    for (int i = aLength - 1; i >= 0; i--)
        cout << a[i];
    cout << " + ";
    for (int i = bLength - 1; i >= 0; i--)
        cout << b[i];
    cout << " = ";
    for (int i = ansLength - 1; i >= 0; i--)
        cout << ans[i];
    cout << endl;
    if (t < caseNum)
        cout << endl;
}

void scan()
{
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(ans, 0, sizeof(ans));
    string str;
    cin >> str;
    aLength = str.length();
    for (int i = 0; i < aLength; i++)
        a[aLength - i - 1] = str[i] - '0';
    cin >> str;
    bLength = str.length();
    for (int i = 0; i < bLength; i++)
        b[bLength - i - 1] = str[i] - '0';
}

void add()
{
    int maxLength = max(aLength, bLength);
    ansLength = maxLength;
    for (int i = 0; i < maxLength; i++)
    {
        ans[i] += a[i] + b[i];
        if (ans[i] > 9)
        {
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
            if (i == maxLength - 1)
                ansLength++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> caseNum;
    for (t = 1; t <= caseNum; t++)
    {
        scan();
        add();
        print();
    }
    return 0;
}
