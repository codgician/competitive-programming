#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <queue>
#include <vector>
#include <set>
#define SIZE 1000001
using namespace std;

int arr[SIZE];

bool cmpRule(int a, int b)
{
    return a > b;
}

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        sort(arr + 0, arr + n, cmpRule);
        for (int i = 0; i < m; i++)
        {
            cout << arr[i];
            if (i < m - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
