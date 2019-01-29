// luogu-judger-enable-o2
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

#define SIZE 1000010
#define OPR_SIZE 1000010

typedef struct _Opr
{
    pair<int, int> pt;
    int qId;    // Insertion: qId = -1

    bool operator < (const struct _Opr & snd) const
    {
        return pt < snd.pt;
    }
} Opr;

Opr oprArr[OPR_SIZE], cntArr[OPR_SIZE];
int ansArr[SIZE], siz;

int bitArr[SIZE];

int getLowbit(int n)
{
    return n & -n;
}

void update(int pos, int val)
{
    for (int i = pos; i < siz; i += getLowbit(i))
    {
        bitArr[i] = max(bitArr[i], val);
    }
}

void clear(int pos)
{
    for (int i = pos; i < siz; i += getLowbit(i))
        bitArr[i] = INT_MIN;
}

int prefixMax(int pos)
{
    int ans = INT_MIN;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans = max(ans, bitArr[i]);
    }
    return ans;
}

void work(int headPt, int tailPt, int dx, int dy)
{
    int inc = 1;
    if (tailPt == 0)
        inc = -1;

    tailPt += inc;
    for (int i = headPt; i != tailPt; i += inc)
    {
        int cnt = dx * cntArr[i].pt.first + dy * cntArr[i].pt.second;
        int y = dy == 1 ? cntArr[i].pt.second : siz - cntArr[i].pt.second;
        if (oprArr[cntArr[i].qId].qId == -1)    // modify
            update(y, cnt);
        else    // query
        {
            int origId = oprArr[cntArr[i].qId].qId;
            if (prefixMax(y) != INT_MIN)
                ansArr[origId] = min(ansArr[origId], abs(cnt - prefixMax(y)));
        }
    }

    for (int i = headPt; i != tailPt; i += inc)
    {
        int y = dy == 1 ? cntArr[i].pt.second : siz - cntArr[i].pt.second;
        if (oprArr[cntArr[i].qId].qId == -1)
            clear(y);
    }
}

void divideConquer(int headPt, int tailPt)
{
    if (headPt == tailPt)
        return;

    int midPt = (headPt + tailPt) >> 1;

    if (headPt < midPt)
        divideConquer(headPt, midPt);
    if (midPt + 1 < tailPt)
        divideConquer(midPt + 1, tailPt);

    // How modifications in the left part afffect queries in the right part
    int cntPt = 0;
    for (int i = headPt; i <= tailPt; i++)
    {
        if ((i <= midPt && oprArr[i].qId == -1) || (i > midPt && oprArr[i].qId > -1))
        {
            cntArr[cntPt] = oprArr[i];
            cntArr[cntPt++].qId = i;    // In cntArr, qId means original id in oprArr
        }
    }

    if (cntPt == 0)
        return;

    sort(cntArr + 0, cntArr + cntPt);
    work(0, cntPt - 1, 1, 1);   // -> x + y     (x1 + y1) - (x2 + y2)
    work(0, cntPt - 1, 1, -1);  // -> x - y     (x1 - y1) - (x2 - y2)
    work(cntPt - 1, 0, -1, -1); // <- -x - y    (-x1 - y1) - (-x2 - y2)
    work(cntPt - 1, 0, -1, 1);  // <- -x + y    (-x1 + y1) - (-x2 + y2)
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num, oprNum;
    cin >> num >> oprNum;

    int oprPt = 0, qPt = 0;
    siz = 0;
    for (int i = 0; i < num; i++)
    {
        pair<int, int> pt;
        cin >> pt.first >> pt.second;
        pt.second++;
        oprArr[oprPt++] = {pt, -1};
        siz = max(siz, pt.second);
    }

    while (oprNum--)
    {
        int opr;
        pair<int, int> pt;
        cin >> opr >> pt.first >> pt.second;
        pt.second++;
        if (opr == 1)
            oprArr[oprPt++] = {pt, -1};
        else
        {
            ansArr[qPt] = INT_MAX;
            oprArr[oprPt++] = {pt, qPt++};
        }
        siz = max(siz, pt.second);
    }

    siz++;
    for (int i = 0; i < siz; i++)
        bitArr[i] = INT_MIN;

    divideConquer(0, oprPt - 1);

    for (int i = 0; i < qPt; i++)
        cout << ansArr[i] << '\n';

    return 0;
}