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
#define FST_SIZE 51
#define SND_SIZE 10010
using namespace std;

long long int fstArr[FST_SIZE], sndArr[SND_SIZE];
long long int num[SND_SIZE];  // Number of elements in original set whose value is i
long long int dp[SND_SIZE];   // Number of subsets whose sum is i

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        memset(dp, 0, sizeof(dp));
        int fstLen, sndLen;
        scanf("%d%d", &fstLen, &sndLen);
        for (int i = 0; i <= sndLen; i++)
            scanf("%lld", sndArr + i);

        int fstPt = 0;
        dp[0] = 1;
        for (int i = 1; i <= sndLen; i++)
        {
            num[i] = sndArr[i] - dp[i];
            for (int j = 0; j < num[i]; j++)
            {
                fstArr[fstPt++] = i;
                for (int k = sndLen; k >= i; k--)
                {
                    dp[k] += dp[k - i];
                }
            }
        }

        for (int i = 0; i < fstPt; i++)
        {
            printf("%lld", fstArr[i]);
            if (i < fstPt - 1)
                printf(" ");
            else
                printf("\n");
        }
    }
    return 0;
}