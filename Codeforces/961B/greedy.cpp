#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 100010
using namespace std;

int lec[SIZE];
bool beh[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int len, k;
    cin >> len >> k;
    for (int i = 0; i < len; i++)
    {
        cin >> lec[i];
    }

    int ans = 0;
    for (int i = 0; i < len; i++)
    {
        cin >> beh[i];
        if (beh[i])
            ans += lec[i];
    }

    int maxInc = 0;
    for (int i = 0; i < k; i++)
    {
        if (!beh[i])
            maxInc += lec[i];
    }

    int cntInc = maxInc;
    for (int i = k; i < len; i++)
    {
        if (!beh[i - k])
            cntInc -= lec[i - k];
        if (!beh[i])
            cntInc += lec[i];
        maxInc = max(maxInc, cntInc);
    }

    cout << ans + maxInc << endl;
    return 0;
}
