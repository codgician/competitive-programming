#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 20100
using namespace std;

typedef struct _Cow
{
    int cord;
    int volume;
} Cow;

Cow arr[SIZE];

long long int leftNumBit[SIZE], leftCordSumBit[SIZE];
int cowNum;

bool cmpRule(Cow a, Cow b)
{
    return a.volume < b.volume;
}

int getLowbit(int n)
{
    return n & -n;
}

void add(long long int *bitArr, int pos, int val)
{
    for (int i = pos; i < SIZE; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

long long int getSum(long long int *bitArr, int pos)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> cowNum)
    {
        memset(leftNumBit, 0, sizeof(leftNumBit));
        memset(leftCordSumBit, 0, sizeof(leftCordSumBit));

        for (int i = 0; i < cowNum; i++)
        {
            cin >> arr[i].volume >> arr[i].cord;
        }

        sort(arr + 0, arr + cowNum, cmpRule);

        long long int cordSum = 0, ans = 0;
        for (int i = 0; i < cowNum; i++)
        {
            long long int leftNum = getSum(leftNumBit, arr[i].cord);
            long long int leftCordSum = getSum(leftCordSumBit, arr[i].cord);
            ans += arr[i].volume * (leftNum * arr[i].cord - leftCordSum);
            ans += arr[i].volume * ((cordSum - leftCordSum) - (i - leftNum) * arr[i].cord);

            cordSum += arr[i].cord;
            add(leftNumBit, arr[i].cord + 1, 1);
            add(leftCordSumBit, arr[i].cord, arr[i].cord);
        }
        cout << ans << endl;
    }
    return 0;
}
