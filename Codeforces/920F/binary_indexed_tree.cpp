#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 300002
#define MAX_NUM 1000001
using namespace std;

long long int bit[SIZE], skipUpdateBit[SIZE];
int divisorNum[MAX_NUM];
int elementNum;

void init()
{
    memset(divisorNum, 0, sizeof(divisorNum));
    divisorNum[0] = 1;
    for (int i = 2; i < MAX_NUM; i++)
    {
        divisorNum[i]++;
        for (int j = i - 1; j < MAX_NUM; j += i)
        {
            divisorNum[j]++;
        }
    }
}

int getLowbit(int n)
{
    return n & (-n);
}

void add(long long int *bitArr, int pos, int val)
{
    for (int i = pos; i <= elementNum; i += getLowbit(i))
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

long long int getVal(long long int *bitArr, int pos)
{
    return getSum(bitArr, pos) - getSum(bitArr, pos - 1);
}

void update(int leftPt, int rightPt)
{
    if (leftPt == rightPt)
    {
        if (!getVal(skipUpdateBit, leftPt))
        {
            int oldVal = getVal(bit, leftPt);
            int newVal = divisorNum[oldVal - 1];
            add(bit, leftPt, newVal - oldVal);
            if (newVal <= 2)
            {
                add(skipUpdateBit, leftPt, 1);
            }
        }
        return;
    }

    if (getSum(skipUpdateBit, rightPt) - getSum(skipUpdateBit, leftPt - 1) == rightPt - leftPt + 1)
        return;

    int midPt = (leftPt + rightPt) >> 1;

    update(leftPt, midPt);
    if (midPt < rightPt)
        update(midPt + 1, rightPt);
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();
    int queryNum;
    cin >> elementNum >> queryNum;
    memset(bit, 0, sizeof(bit));
    memset(skipUpdateBit, 0, sizeof(skipUpdateBit));
    for (int i = 1; i <= elementNum; i++)
    {
        int tmp;
        cin >> tmp;
        add(bit, i, tmp);
        if (tmp <= 2)
        {
            add(skipUpdateBit, i, 1);
        }
    }

    while (queryNum--)
    {
        int oprType, leftPt, rightPt;
        cin >> oprType >> leftPt >> rightPt;
        if (oprType == 1)
        {
            update(leftPt, rightPt);
        }
        else
        {
            cout << getSum(bit, rightPt) - getSum(bit, leftPt - 1) << endl;
        }
    }

    return 0;
}
