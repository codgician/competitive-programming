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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 110
using namespace std;

typedef struct _Node
{
    long long int size, value;
    double rank;
} Node;

Node arr[SIZE];
int num;
long long int lim, ans;

bool cmpRule(Node &a, Node &b)
{
    return a.rank > b.rank;
}

bool canMove(int step, long long int cntSize, long long int cntValue)
{
    for (int i = step; i < num && cntSize < lim; i++)
    {
        if (cntSize + arr[i].size <= lim)
        {
            cntSize += arr[i].size;
            cntValue += arr[i].value;
        }
        else
        {
            cntValue += arr[i].rank * (lim - cntSize);
            cntSize = lim;
        }
    }
    return cntValue > ans;
}

void dfs(int step, long long int cntSize, long long int cntValue)
{
    ans = max(ans, cntValue);
    if (step < num && canMove(step, cntSize, cntValue))
    {
        if (cntSize + arr[step].size <= lim)
        {
            dfs(step + 1, cntSize + arr[step].size, cntValue + arr[step].value);
        }
        dfs(step + 1, cntSize, cntValue);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> num >> lim)
    {
        ans = 0;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].size >> arr[i].value;
            if (arr[i].size > lim)
            {
                num--;
                i--;
            }
            else
            {
                arr[i].rank = (double)arr[i].value / arr[i].size;
            }
        }

        sort(arr + 0, arr + num, cmpRule);
        dfs(0, 0, 0);
        cout << ans << endl;
    }
    return 0;
}