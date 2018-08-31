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

#define SIZE 100010

const int mod = 1 << 30;

typedef struct _Node
{
    int x, y, z;
} Node;

Node arr[SIZE];

typedef struct _Ans
{
    int len, num;

    void update(const struct _Ans & snd)
    {
        if (len < snd.len)
        {
            len = snd.len;
            num = snd.num;
        }
        else if (len == snd.len)
        {
            num += snd.num;
            if (num >= mod)
                num %= mod;
        }
    }
} Ans;

Ans dp[SIZE];
int num;

int zArr[SIZE];
Ans bitArr[SIZE];

int getLowbit(int n)
{
    return n & -n;
}

void clear(int pos)
{
    for (int i = pos; i < SIZE; i += getLowbit(i))
    {
        bitArr[i] = {0, 0};
    }
}

void update(int pos, const Ans & val)
{
    for (int i = pos; i < SIZE; i += getLowbit(i))
    {
        bitArr[i].update(val);
    }
}

Ans getPrefixMax(int pos)
{
    Ans ans = {0, 0};
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans.update(bitArr[i]);
    }
    return ans;
}

bool cmpY(Node & fst, Node & snd)
{
    if (fst.y == snd.y)
        return fst.z < snd.z;
    return fst.y < snd.y;
}

bool cmpX(Node & fst, Node & snd)
{
    if (fst.x == snd.x)
        return cmpY(fst, snd);
    return fst.x < snd.x;
}

void divideConquer(int leftPt, int rightPt)
{
    if (leftPt == rightPt)
        return;

    int midPt = (leftPt + rightPt) >> 1;
    divideConquer(leftPt, midPt);
    
    sort(arr + leftPt, arr + midPt + 1, cmpY);
    sort(arr + midPt + 1, arr + rightPt + 1, cmpY);

    int j = leftPt;
    for (int i = midPt + 1; i <= rightPt; i++)
    {
        for (; j <= midPt && arr[j].y <= arr[i].y; j++)
        {
            update(arr[j].z + 1, dp[arr[j].x]);
        }

        Ans cnt = getPrefixMax(arr[i].z + 1);
        cnt.len++;
        dp[arr[i].x].update(cnt);
    }

    for (int i = leftPt; i <= j; i++)
        clear(arr[i].z + 1);

    sort(arr + midPt + 1, arr + rightPt + 1, cmpX);
    divideConquer(midPt + 1, rightPt);
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
        for (int i = 1; i <= num; i++)
        {
            bitArr[i] = {0, 0};
        }

        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].x >> arr[i].y >> arr[i].z;
            zArr[i] = arr[i].z;
        }

        sort(zArr + 0, zArr + num);
        int zNum = unique(zArr + 0, zArr + num) - zArr;
        sort(arr + 0, arr + num, cmpX);

        for (int i = 0; i < num; i++)
        {
            arr[i].x = i;
            arr[i].z = lower_bound(zArr + 0, zArr + zNum, arr[i].z) - zArr;
            dp[i] = {1, 1};
        }

        divideConquer(0, num - 1);

        Ans ans = {0, 0};
        for (int i = 0; i < num; i++)
        {
            ans.update(dp[i]);
        }

        cout << ans.len << " " << ans.num << endl; 
    }

    return 0;
}