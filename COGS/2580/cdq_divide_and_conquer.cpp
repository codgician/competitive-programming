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
#include <cassert>
using namespace std;

#define SIZE 50010

#define LEFT false
#define RIGHT true

typedef struct _Node
{
    int val[5];
    bool flag[2];

    bool operator == (const struct _Node & snd) const
    {
        for (int i = 0; i < 5; i++)
            if (val[i] != snd.val[i])
                return false;
        return true;
    }
} Node;

bool cmpFor(const Node & fst, const Node & snd)
{
    if (fst.val[3] != snd.val[3])
        return fst.val[3] < snd.val[3];
    return fst.val[4] < snd.val[4];
}

bool cmpThd(const Node & fst, const Node & snd)
{
    if (fst.val[2] != snd.val[2])
        return fst.val[2] < snd.val[2];
    return cmpFor(fst, snd);
}

bool cmpSnd(const Node & fst, const Node & snd)
{
    if (fst.val[1] != snd.val[1])
        return fst.val[1] < snd.val[1];
    return cmpThd(fst, snd);
}

Node arr[SIZE], tmp[SIZE];
int bitArr[SIZE], siz, ans;

int getLowbit(int n)
{
    return n & -n;
}

void add(int pos, int val)
{
    for (int i = pos; i <= siz; i += getLowbit(i))
        bitArr[i] += val;
}

void clear(int pos)
{
    for (int i = pos; i <= siz; i += getLowbit(i))
    {
        bitArr[i] = 0;
    }
}

int prefixSum(int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
        ans += bitArr[i];
    return ans;
}

void divideConquer2D(int headPt, int tailPt)
{
    if (headPt >= tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;

    divideConquer2D(headPt, midPt);
    divideConquer2D(midPt + 1, tailPt);

    sort(arr + headPt, arr + midPt + 1, cmpFor);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpFor);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++)
    {
        for (; j <= midPt && arr[j].val[3] < arr[i].val[3]; j++)
            if (arr[j].flag[0] == LEFT && arr[j].flag[1] == LEFT)
                add(arr[j].val[4], 1);
        if (arr[i].flag[0] == RIGHT && arr[i].flag[1] == RIGHT)
            ans += prefixSum(arr[i].val[4]);
    }

    for (int i = headPt; i < j; i++)
        if (arr[i].flag[0] == LEFT && arr[i].flag[1] == LEFT)
            clear(arr[i].val[4]);
}

void divideConquer3D(int headPt, int tailPt)
{
    if (headPt >= tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;

    divideConquer3D(headPt, midPt);
    divideConquer3D(midPt + 1, tailPt);

    sort(arr + headPt, arr + midPt + 1, cmpThd);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpThd);

    int leftPt = headPt, rightPt = midPt + 1, tmpPt = 0;
    while (leftPt <= midPt && rightPt <= tailPt)
    {
        if (arr[leftPt].val[2] < arr[rightPt].val[2])
        {
            tmp[tmpPt] = arr[leftPt++];
            tmp[tmpPt++].flag[1] = LEFT;
        }
        else
        {
            tmp[tmpPt] = arr[rightPt++];
            tmp[tmpPt++].flag[1] = RIGHT;
        }
    }
    while (leftPt <= midPt)
    {
        tmp[tmpPt] = arr[leftPt++];
        tmp[tmpPt++].flag[1] = LEFT;
    }
    while (rightPt <= tailPt)
    {
        tmp[tmpPt] = arr[rightPt++];
        tmp[tmpPt++].flag[1] = RIGHT;
    }

    for (int i = 0; i < tmpPt; i++)
        arr[headPt + i] = tmp[i];
    divideConquer2D(headPt, tailPt);
}

void divideConquer4D(int headPt, int tailPt)
{
    if (headPt >= tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;

    divideConquer4D(headPt, midPt);
    divideConquer4D(midPt + 1, tailPt);

    sort(arr + headPt, arr + midPt + 1, cmpSnd);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpSnd);

    int leftPt = headPt, rightPt = midPt + 1, tmpPt = 0;
    while (leftPt <= midPt && rightPt <= tailPt)
    {
        if (arr[leftPt].val[1] < arr[rightPt].val[1])
        {
            tmp[tmpPt] = arr[leftPt++];
            tmp[tmpPt++].flag[0] = LEFT;
        }
        else
        {
            tmp[tmpPt] = arr[rightPt++];
            tmp[tmpPt++].flag[0] = RIGHT;
        }
    }
    while (leftPt <= midPt)
    {
        tmp[tmpPt] = arr[leftPt++];
        tmp[tmpPt++].flag[0] = LEFT;
    }
    while (rightPt <= tailPt)
    {
        tmp[tmpPt] = arr[rightPt++];
        tmp[tmpPt++].flag[0] = RIGHT;
    }

    for (int i = 0; i < tmpPt; i++)
        arr[headPt + i] = tmp[i];
    divideConquer3D(headPt, tailPt);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("partial_order_two.in", "r", stdin);
    freopen("partial_order_two.out", "w", stdout);
    
    memset(bitArr, 0, sizeof(bitArr));
    siz = 0, ans = 0;

    int num;
    cin >> num;
    for (int j = 1; j < 5; j++)
    {
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].val[j];
            arr[i].val[0] = i;
            siz = max(siz, arr[i].val[j]);
        }
    }

    divideConquer4D(0, num - 1);

    cout << ans << '\n';

    return 0;
}