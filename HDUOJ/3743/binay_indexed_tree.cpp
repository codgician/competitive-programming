#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define SIZE 1000010
using namespace std;

long long int bitArr[SIZE], arr[SIZE], tmpArr[SIZE];
int bitSize;

int getLowbit(int n)
{
    return n & -n;
}

void add(int pos, long long int val)
{
    for (int i = pos; i <= bitSize; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

long long int getSum(int pos)
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
    while (cin >> bitSize)
    {
        memset(bitArr, 0, sizeof(bitArr));
        for (int i = 1; i <= bitSize; i++)
        {
            cin >> arr[i];
            tmpArr[i] = arr[i];
        }

        sort(tmpArr + 1, tmpArr + bitSize + 1);

        for (int i = 1; i <= bitSize; i++)
        {
            arr[i] = upper_bound(tmpArr + 1, tmpArr + bitSize + 1, arr[i]) - tmpArr - 1;
        }

        long long int ans = 0;
        for (int i = bitSize; i > 0; i--)
        {
            ans += getSum(arr[i] - 1);
            add(arr[i], 1);
        }

        cout << ans << endl;
    }
    return 0;
}
