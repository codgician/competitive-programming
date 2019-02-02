#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <cassert>
using namespace std;

#define SIZE 40010
#define OFF_SIZE 20
#define STATE_SIZE 70010

int pfxArr[SIZE], oprArr[SIZE];
int cost[SIZE], dp[STATE_SIZE], posArr[OFF_SIZE];
int num, offNum, oprNum;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // 0: On, 1: Off
    // Anticipated xor prefix pfxArray: 0 0 .. 0
    memset(pfxArr, 0, sizeof(pfxArr));

    cin >> num >> offNum >> oprNum;
    for (int i = 0; i < offNum; i++)
    {
        int pos;
        cin >> pos;
        pfxArr[--pos] = 1;
    }

    for (int i = 0; i < oprNum; i++)
        cin >> oprArr[i];

    cost[0] = 0;
    for (int i = 1; i <= num; i++)
        cost[i] = INT_MAX;
    for (int i = 0; i < oprNum; i++)
        for (int j = oprArr[i]; j <= num; j++)
            if (cost[j - oprArr[i]] != INT_MAX)
                cost[j] = min(cost[j], cost[j - oprArr[i]] + 1);
    for (int i = 0; i < oprNum; i++)
        for (int j = num - oprArr[i]; j >= 0; j--)
            if (cost[j + oprArr[i]] != INT_MAX)
                cost[j] = min(cost[j], cost[j + oprArr[i]] + 1);

    // Transform into xor prefix pfxArray
    for (int i = num - 1; i > 0; i--)
        pfxArr[i] ^= pfxArr[i - 1];

    int posPt = 0;
    for (int i = 0; i < num; i++)
        if (pfxArr[i])
            posArr[posPt++] = i;
    int stateNum = 1 << posPt;
    for (int i = 0; i < stateNum; i++)
        dp[i] = INT_MAX;
    dp[stateNum - 1] = 0;
    for (int i = stateNum - 1; i > 0; i--)
    {
        int fstPt = 0;
        while (!(i & (1 << fstPt)))
            fstPt++;

        // fstPt -> fstPt
        if (cost[num - posArr[fstPt]] != INT_MAX)
        {
            int nextState = i ^ (1 << fstPt); 
            if (cost[num - posArr[fstPt]] != INT_MAX && dp[i] != INT_MAX)
                dp[nextState] = min(dp[nextState], dp[i] + cost[num - posArr[fstPt]]);
        }

        // fstPt -> sndPt
        for (int sndPt = fstPt + 1; sndPt < posPt; sndPt++)
        {
            if (!(i & (1 << sndPt)))
                continue;
            int nextState = i ^ (1 << fstPt) ^ (1 << sndPt);
            if (cost[posArr[sndPt] - posArr[fstPt]] != INT_MAX && dp[i] != INT_MAX)
                dp[nextState] = min(dp[nextState], dp[i] + cost[posArr[sndPt] - posArr[fstPt]]);
        }
    }

    cout << dp[0] << endl;

    return 0;
}