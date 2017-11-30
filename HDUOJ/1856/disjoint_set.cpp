#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10000001
using namespace std;

int arr[SIZE], num[SIZE];
int ans = 0;

int getParent(int n)
{
    if (arr[n] == n)
        return n;
    else
    {
        arr[n] = getParent(arr[n]);
        return arr[n];
    }
}

void mergeFriend(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        arr[bParent] = aParent;
        num[aParent] += num[bParent];
        ans = max(ans, num[aParent]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int pairNum;
    while (cin >> pairNum)
    {
        ans = 0;
        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = i;
            num[i] = 1;
        }

        for (int i = 0; i < pairNum; i++)
        {
            int a, b;
            cin >> a >> b;
            mergeFriend(a - 1, b - 1);
        }

        if (ans == 0)
            ans = 1;
        cout << ans << endl;
    }
    return 0;
}
