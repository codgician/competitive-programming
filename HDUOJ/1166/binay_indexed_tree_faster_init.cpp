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
#define SIZE 50010
using namespace std;

long long int bitArr[SIZE];
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
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        cin >> bitSize;
        for (int i = 1; i <= bitSize; i++)
        {
            long long int cnt;
            cin >> cnt;
            bitArr[i] = cnt;

            int len = getLowbit(i) >> 1;
            int cntPt = i - len;
            while (len > 0)
            {
                bitArr[i] += bitArr[cntPt];
                len >>= 1;
                cntPt += len;
            }
        }

        cout << "Case " << t << ":" << endl;
        string opr;
        while (cin >> opr)
        {
            if (opr == "Add")
            {
                int pos;
                long long int val;
                cin >> pos >> val;
                add(pos, val);
            }
            else if (opr == "Sub")
            {
                int pos;
                long long int val;
                cin >> pos >> val;
                add(pos, -val);
            }
            else if (opr == "Query")
            {
                int leftPt, rightPt;
                cin >> leftPt >> rightPt;

                long long int ans = getSum(rightPt) - getSum(leftPt - 1);
                cout << ans << endl;
            }
            else if (opr == "End")
            {
                break;
            }
        }
    }
    return 0;
}
