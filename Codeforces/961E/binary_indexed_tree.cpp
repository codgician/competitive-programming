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
#define SIZE 200010
using namespace std;

typedef struct _Node
{
    int id;
    int epiNum;
} Node;

Node tmp[SIZE];
int arr[SIZE], bitArr[SIZE];
int seaNum;

bool cmpRule(Node &a, Node &b)
{
    return a.epiNum < b.epiNum;
}

int getLowbit(int n)
{
    return n & -n;
}

void add(int pos, int val)
{
    for (int i = pos; i <= seaNum; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int getSum(int pos)
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
    memset(bitArr, 0, sizeof(bitArr));
    cin >> seaNum;

    for (int i = 1; i <= seaNum; i++)
    {
        cin >> arr[i];
        arr[i] = min(arr[i], seaNum);

        tmp[i].id = i;
        tmp[i].epiNum = arr[i];

        add(i, 1);
    }

    sort(tmp + 1, tmp + seaNum + 1, cmpRule);

    long long int ans = 0;
    int tmpPt = 1;
    for (int i = 1; i <= seaNum; i++)
    {
        while (tmpPt <= seaNum && tmp[tmpPt].epiNum < i)
        {
            add(tmp[tmpPt].id, -1);
            tmpPt++;
        }

        ans += getSum(arr[i]);
        if (arr[i] >= i)
            ans--;
    }

    cout << (ans >> 1) << endl;

    return 0;
}
