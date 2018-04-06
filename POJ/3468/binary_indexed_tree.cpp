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
#define SIZE 100100
using namespace std;

long long int arr[SIZE], bitArr[2][SIZE];
int arrLen;

int getLowbit(int n)
{
    return n & -n;
}

void add(int bitId, int pos, long long int val)
{
    for (int i = pos; i <= arrLen; i += getLowbit(i))
        bitArr[bitId][i] += val;
}

long long int query(int bitId, int pos)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
        ans += bitArr[bitId][i];
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int oprNum;
    while (cin >> arrLen >> oprNum)
    {
        memset(bitArr, 0, sizeof(bitArr));
        arr[0] = 0;
        for (int i = 1; i <= arrLen; i++)
        {
            long long int cnt;
            cin >> cnt;
            arr[i] = arr[i - 1] + cnt;
        }

        while (oprNum--)
        {
            char op;
            int leftPt, rightPt;
            cin >> op >> leftPt >> rightPt;

            if (op == 'Q')
            {
                long long int ans = arr[rightPt] + (rightPt + 1) * query(0, rightPt) - query(1, rightPt);
                ans -= arr[leftPt - 1] + leftPt * query(0, leftPt - 1) - query(1, leftPt - 1);
                cout << ans << endl;
            }
            else if(op == 'C')
            {
                long long int val;
                cin >> val;

                add(0, leftPt, val);
                add(0, rightPt + 1, -val);
                add(1, leftPt, leftPt * val);
                add(1, rightPt + 1, -(rightPt + 1) * val);
            }
        }
    }
    return 0;
}
