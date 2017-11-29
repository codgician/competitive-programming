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

int arr[SIZE];

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

void mergeTown(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        arr[bParent] = aParent;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int townNum, roadNum;
    while (cin >> townNum)
    {
        if (townNum == 0)
            break;

        cin >> roadNum;

        for (int i = 0; i < townNum; i++)
        {
            arr[i] = i;
        }

        for (int i = 0; i < roadNum; i++)
        {
            int a, b;
            cin >> a >> b;
            mergeTown(a - 1, b - 1);
        }

        int ans = 0;
        for (int i = 0; i < townNum; i++)
        {
            if (arr[i] == i)
                ans++;
        }
        cout << ans - 1 << endl;
    }
    return 0;
}
