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
    {
        return n;
    }
    else
    {
        // Route compression.
        arr[n] = getParent(arr[n]);
        return arr[n];
    }
}

void mergeFriends(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        arr[bParent] = aParent;
    }

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int friendNum, relationNum;
        cin >> friendNum >> relationNum;

        for (int i = 0; i < friendNum; i++)
        {
            arr[i] = i;
        }

        for (int i = 0; i < relationNum; i++)
        {
            int a, b;
            cin >> a >> b;
            mergeFriends(a - 1, b - 1);
        }

        int ans = 0;
        for (int i = 0; i < friendNum; i++)
        {
            if (arr[i] == i)
            {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
