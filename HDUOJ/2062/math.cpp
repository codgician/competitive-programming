#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#define SIZE 21
using namespace std;

long long int setSize, m;
long long int length, n;

bool isUsed[SIZE];

long long int getNth(long long int n)
{
    long long int ans = 0, i = 0;
    for (ans = 0; ans < setSize; ans++)
    {
        if (!isUsed[ans])
            i++;
        if (i == n)
            break;
    }
    isUsed[ans] = true;
    return ans + 1;
}

long long int getA(long long int m, long long int n)
{
    if (m == 0)
        return 1;
    long long int ans = n;
    for (long long int i = n - 1; i > n - m; i--)
    {
        ans *= i;
    }
    return ans;
}

long long int getGroupNum(long long int subsetSize)
{
    long long int ans = 0;
    for (long long int i = 0; i <= subsetSize - 1; i++)
        ans += getA(i, subsetSize - 1);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> setSize >> m)
    {
        memset(isUsed, false, sizeof(isUsed));
        long long int groupNum = getGroupNum(setSize);
        long long int cntSetSize = setSize;
        bool isFirst = true;
        while (cntSetSize > 0)
        {
            if (isFirst)
                isFirst = false;
            else
                cout << " ";
            if (m % groupNum == 0)
            {
                cout << getNth(m / groupNum);
                m = groupNum - 1;
            }
            else
            {
                cout << getNth(m / groupNum + 1);
                m %= groupNum;
                m -= 1;
            }
            if (m == 0)
                break;
            groupNum = getGroupNum(--cntSetSize);
        }
        cout << endl;
    }
    return 0;
}
