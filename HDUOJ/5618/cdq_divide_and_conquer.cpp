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

#define SIZE 100100

typedef struct _Node
{
    int x, y, z;
    int id;
} Node;

Node arr[SIZE], tmp[SIZE];

int dp[SIZE];
int num;
int bitArr[SIZE];

int getLowbit(int n)
{
    return n & -n;
}

void clear(int pos)
{
    for (int i = pos; i < SIZE; i += getLowbit(i))
    {
        bitArr[i] = 0;
    }
}

void add(int pos, int val)
{
    for (int i = pos; i < SIZE; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int getPrefixSum(int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
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
            add(arr[j].z + 1, 1);
        }

        dp[arr[i].id] += getPrefixSum(arr[i].z + 1);
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
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].x >> arr[i].y >> arr[i].z;
            arr[i].id = i;
        }
        sort(arr + 0, arr + num, cmpX);

        memset(dp, 0, sizeof(dp));
        memset(bitArr, 0, sizeof(bitArr));

        divideConquer(0, num - 1);
        for (int i = num - 2; i >= 0; i--)
        {
            if (arr[i].x == arr[i + 1].x && arr[i].y == arr[i + 1].y && arr[i].z == arr[i + 1].z)
            {
                dp[arr[i].id] = dp[arr[i + 1].id];
            }
        }

        for (int i = 0; i < num; i++)
        {
            cout << dp[i] << endl;
        }
    }

    return 0;
}