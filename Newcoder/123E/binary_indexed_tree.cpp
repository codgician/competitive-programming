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

#define SIZE 1000100

int arr[SIZE];
int pre[SIZE], aff[SIZE];
int posBit[SIZE], oneBit[SIZE];

int num;

inline int getLowbit(int n)
{
    return n & (-n);
}

inline void add(int *bitArr, int pos, int val)
{
    for (int i = pos; i <= num; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

inline int getPrefixSum(int *bitArr, int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

inline int getSuffixSum(int *bitArr, int pos)
{
    return getPrefixSum(bitArr, num) - getPrefixSum(bitArr, pos - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> num;
        for (int i = 0; i <= num; i++)
        {
            posBit[i] = 0;
            oneBit[i] = 0;
        }

        for (int i = 1; i <= num; i++)
        {
            cin >> arr[i];
            pre[i] = getPrefixSum(posBit, arr[i]);
            if (pre[i] > 0)
                aff[i] = 1;
            add(posBit, arr[i], 1);
        }

        for (int i = num; i >= 1; i--)
        {
            if (pre[i] == 1)
                add(oneBit, arr[i], 1);
            else if (pre[i] == 0)
                aff[i] = getSuffixSum(oneBit, arr[i]);
        }

        int delNum = INT_MAX, affectNum = INT_MAX;
        for (int i = 1; i <= num; i++)
        {
            if (aff[i] < affectNum || (aff[i] == affectNum && arr[i] < delNum))
            {
                delNum = arr[i];
                affectNum = aff[i];
            }
        }

        cout << delNum << endl;
    }
    return 0;
}