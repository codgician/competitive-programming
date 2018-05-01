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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 500010
using namespace std;

const int mod = 1e9;

int arr[SIZE];
long long int sumArr[32][SIZE];

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int intNum, qNum;
        scanf("%d%d", &intNum, &qNum);
        for (int i = 1; i <= intNum; i++)
        {
            scanf("%d", arr + i);
        }
        sort(arr + 1, arr + intNum + 1);
        for (int i = 1; i <= 31; i++)
        {
            sumArr[i][0] = 0;
            for (int j = 1; j <= intNum; j++)
            {
                sumArr[i][j] = (sumArr[i][j - 1] + arr[j] / i) % mod;
            }
        }

        long long int ans = 0;
        for (int i = 1; i <= qNum; i++)
        {
            long long int cntAns = 0;
            int p;
            scanf("%d", &p);
            for (int k = 1, leftPt = 1, cnt = 1; k <= 31 && leftPt <= intNum; k++)
            {
                if (cnt > 1e9 / p)
                    cnt = 1e9 + 1;
                else
                    cnt *= p;

                int rightPt = upper_bound(arr + 1, arr + intNum + 1, cnt) - arr;
                cntAns = (cntAns + sumArr[k][rightPt - 1] - sumArr[k][leftPt - 1]) % mod;
                leftPt = rightPt;
            }
            ans = (ans + i * cntAns) % mod;
        }
        ans = (ans + mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}