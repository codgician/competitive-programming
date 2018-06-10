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
#define SIZE 100100
using namespace std;

int arr[SIZE], revBit[SIZE], fixBit[SIZE];
int revNum[SIZE], posArr[SIZE];
int len;

inline int getLowbit(int n)
{
    return n & (-n);
}

inline void add(int *bitArr, int pos, int val)
{
    for (int i = pos; i <= len; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

inline int prefixSum(int *bitArr, int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

inline int suffixSum(int *bitArr, int pos)
{
    return prefixSum(bitArr, len) - prefixSum(bitArr, pos - 1);
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        memset(revBit, 0, sizeof(revBit));
        memset(fixBit, 0, sizeof(fixBit));
        scanf("%d", &len);
        for (int i = 1; i <= len; i++)
        {
            scanf("%d", arr + i);
            posArr[arr[i]] = i;
        }

        long long int cntAns = 0;
        for (int i = 1; i <= len; i++)
        {
            revNum[arr[i]] = suffixSum(revBit, arr[i] + 1);
            cntAns += revNum[arr[i]];
            add(revBit, arr[i], 1);
        }

        long long int ans = cntAns;
        for (int i = 1; i <= len; i++)
        {
            cntAns -= revNum[i] + prefixSum(fixBit, posArr[i]);
            revNum[i] = 0;
            cntAns += len - posArr[i];
            add(fixBit, posArr[i] + 1, 1);
            ans = min(ans, cntAns);
        }
        
        printf("%lld\n", ans);
    }
    return 0;
}