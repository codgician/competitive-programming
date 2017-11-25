#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 100001
using namespace std;

long long int cpuArr[SIZE], gfxArr[SIZE];

bool cmpRule (long long int a, long long int b)
{
    return a > b;
}

int main()
{
    ios::sync_with_stdio(false);
    int cpuNum, gfxNum;
    cin >> cpuNum >> gfxNum;

    for (int i = 0; i < cpuNum; i++)
    {
        cin >> cpuArr[i];
    }
    for (int i = 0; i < gfxNum; i++)
    {
        cin >> gfxArr[i];
    }

    int num = min(cpuNum, gfxNum);
    cout << num;

    sort(cpuArr + 0, cpuArr + cpuNum, cmpRule);
    sort(gfxArr + 0, gfxArr + gfxNum, cmpRule);

    long long int ans = 0;
    for (int i = 0; i < num; i++)
    {
        ans += cpuArr[i] * gfxArr[i];
    }

    cout << " " << ans << endl;
    return 0;
}
