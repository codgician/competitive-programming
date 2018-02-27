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
#define BIT_SIZE 100010
using namespace std;

int bit[BIT_SIZE];
int ballNum;

int getLowbit(int n)
{
    return n & (-n);
}

void add(int *bitArr, int pos, int val)
{
    for (int i = pos; i <= ballNum; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int getSum(int *bitArr, int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> ballNum)
    {
        if (ballNum == 0)
            break;

        memset(bit, 0, sizeof(bit));
        for (int i = 0; i < ballNum; i++)
        {
            int startPt, endPt;
            cin >> startPt >> endPt;
            add(bit, startPt, 1);
            add(bit, endPt + 1, -1);
        }

        for (int i = 1; i < ballNum; i++)
            cout << getSum(bit, i) << " ";
        cout << getSum(bit, ballNum) << endl;
    }
    return 0;
}
