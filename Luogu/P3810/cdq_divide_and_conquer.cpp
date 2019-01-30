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

#define SIZE 100010
#define VAL_SIZE 200020

typedef struct _Node
{
    int a, b, c;
    int num, ans;

    bool operator == (const struct _Node & snd) const
    {
        return a == snd.a && b == snd.b && c == snd.c;
    }
} Node;

Node arr[SIZE];
int ansArr[SIZE];

int bitArr[VAL_SIZE], siz;

bool cmpSnd(Node & fst, Node & snd)
{
    if (fst.b != snd.b)
        return fst.b < snd.b;
    return fst.c < snd.c;
}

bool cmpFst(Node & fst, Node & snd)
{
    if (fst.a != snd.a)
        return fst.a < snd.a;
    return cmpSnd(fst, snd);
}

int getLowbit(int n)
{
    return n & -n;
}

void add(int pos, int val)
{
    for (int i = pos; i <= siz; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
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
    {
        ans += bitArr[i];
    }
    return ans;
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

    sort(arr + headPt, arr + midPt + 1, cmpSnd);
    sort(arr + midPt + 1, arr + tailPt + 1, cmpSnd);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++)
    {
        for (; j <= midPt && arr[j].b <= arr[i].b; j++)
        {
            add(arr[j].c, arr[j].num);
        }
        arr[i].ans += prefixSum(arr[i].c);
    }

    for (int i = headPt; i < j; i++)
        clear(arr[i].c);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(ansArr, 0, sizeof(ansArr));
    memset(bitArr, 0, sizeof(bitArr));

    int num;
    cin >> num >> siz;
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i].a >> arr[i].b >> arr[i].c;
        arr[i].num = 1;
        arr[i].ans = 0;
    }

    sort(arr + 0, arr + num, cmpFst);

    int ovrPt = 0, cntPt = 1;
    while (cntPt < num)
    {
        if (arr[ovrPt] == arr[cntPt])
            arr[ovrPt].num += arr[cntPt].num;
        else
            arr[++ovrPt] = arr[cntPt];
        cntPt++;
    }
    ovrPt++;

    divideConquer(0, ovrPt - 1);

    for (int i = 0; i < ovrPt; i++)
    {
        arr[i].ans += arr[i].num - 1;
        ansArr[arr[i].ans] += arr[i].num;
    }

    for (int i = 0; i < num; i++)
        cout << ansArr[i] << '\n';

    return 0;
}