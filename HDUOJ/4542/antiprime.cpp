#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 48000
#define INF (((long long int)1 << 62) + 1)
using namespace std;

int primeArr[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
int oneAnsArr[SIZE];
long long int zeroAns;

void init()
{
    for (int i = 1; i < SIZE; i++)
        oneAnsArr[i] = i;

    for (int i = 1; i < SIZE; i++)
    {
        for (int j = i; j < SIZE; j += i)
            oneAnsArr[j]--;

        if (oneAnsArr[oneAnsArr[i]] == 0)
            oneAnsArr[oneAnsArr[i]] = i;

        oneAnsArr[i] = 0;
    }
}


void dfs(int depth, long long int cnt, int factorNum, int upperLimit)
{
    if (factorNum > upperLimit)
        return;

    if (factorNum == upperLimit)
        zeroAns = min(zeroAns, cnt);

    for (int i = 1; factorNum * (i + 1) <= upperLimit; i++)
    {
        if (zeroAns / primeArr[depth] < cnt)
            break;

        cnt *= primeArr[depth];
        if (upperLimit % (factorNum * (i + 1)) == 0)
            dfs(depth + 1, cnt, factorNum * (i + 1), upperLimit);
    }
}

int main()
{
    init();
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int typeId, num;
        scanf("%d%d", &typeId, &num);

        printf("Case %d: ", t);
        if (typeId == 0)
        {
            zeroAns = INF;
            dfs(0, 1, 1, num);
            if (zeroAns >= INF)
                printf("INF\n");
            else
                printf("%lld\n", zeroAns);
        }
        else
        {
            if (oneAnsArr[num] == 0)
                printf("Illegal\n");
            else
                printf("%d\n", oneAnsArr[num]);
        }
    }
    return 0;
}