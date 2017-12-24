#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10001
using namespace std;

int father[SIZE], expColor[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    father[0] = 0;
    for (int i = 1; i < SIZE; i++)
        father[i] = -1;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        tmp--;
        if (i < tmp)
            father[tmp] = i;
        else
            father[i] = tmp;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> expColor[i];
    }

    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        if (expColor[i] != expColor[father[i]])
            ans++;
    }
    cout << ans << endl;
    return 0;
}
