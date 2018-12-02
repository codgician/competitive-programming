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
using namespace std;

const long long int mod = 1e9 + 7;

typedef struct _Node
{
    int leftPt, rightPt;
    long long int section;
} Node;

Node arr[30];

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int arrPt = 0;

        // One
        long long int oneAns = 1;
        for (arrPt = 0; arrPt < 4; arrPt++)
        {
            scanf("%lld%lld", &arr[arrPt].leftPt, &arr[arrPt].rightPt);
            arr[arrPt].section = max(0, arr[arrPt].rightPt - arr[arrPt].leftPt + 1);
            oneAns *= arr[arrPt].section;
            oneAns %= mod;
        }

        // Two: 1 == 2, 2 == 3, 3 == 4, 4 == 1
        long long int twoAns = 0;
        for (int i = 0; i < 4; i++)
        {
            int j = (i + 1) % 4;

            arr[arrPt].leftPt = max(arr[i].leftPt, arr[j].leftPt);
            arr[arrPt].rightPt = min(arr[i].rightPt, arr[j].rightPt);
            arr[arrPt].section = max(0, arr[arrPt].rightPt - arr[arrPt].leftPt + 1);
            if (arr[arrPt].section > 0)
            {
                twoAns += (arr[arrPt].section * arr[(i - 1 + 4) % 4].section % mod) * arr[(j + 1) % 4].section % mod;
                twoAns %= mod;
            }
            
            arrPt++;
        }

        // Two + Two: 1 == 2 && 3 == 4, 2 == 3 && 1 == 4
        long long int twoAndTwoAns = (arr[4].section * arr[6].section % mod + arr[5].section * arr[7].section % mod) % mod;

        // Three: 1 == 2 == 3, 2 == 3 == 4, 3 == 4 == 1, 4 == 1 == 2
        long long int threeAns = 0;
        for (int i = 0; i < 4; i++)
        {
            int j = (i + 1) % 4;
            int k = (j + 1) % 4;

            arr[arrPt].leftPt = max(arr[i].leftPt, max(arr[j].leftPt, arr[k].leftPt));
            arr[arrPt].rightPt = min(arr[i].rightPt, min(arr[j].rightPt, arr[k].rightPt));
            arr[arrPt].section = max(0, arr[arrPt].rightPt - arr[arrPt].leftPt + 1);
            if (arr[arrPt].section > 0)
            {
                threeAns += arr[arrPt].section * arr[(k + 1) % 4].section % mod;
                threeAns %= mod;
            }
            arrPt++;
        }

        // Four
        long long int fourAns = 0;
        arr[arrPt].leftPt = max(max(arr[0].leftPt, arr[1].leftPt), max(arr[2].leftPt, arr[3].leftPt));
        arr[arrPt].rightPt = min(min(arr[0].rightPt, arr[1].rightPt), min(arr[2].rightPt, arr[3].rightPt));
        arr[arrPt].section = max(0, arr[arrPt].rightPt - arr[arrPt].leftPt + 1);
        if (arr[arrPt].section > 0)
        {
            fourAns = arr[arrPt].section;
        }

        long long int ans = (((oneAns - twoAns + mod) % mod + (twoAndTwoAns + threeAns) % mod) % mod - (3 * fourAns) % mod + mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}