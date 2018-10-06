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
#include <bitset>
using namespace std;

#define CORD_SIZE 1010
#define SIZE 20

typedef struct _Node
{
    int x, y;
} Node;

Node arr[SIZE];

bool cntState[SIZE];

map<long long int, int> mp;

long long int ans;
int num;

long long int getId(int ka, int kb, int ksgn)
{
    return (1ll * ka * CORD_SIZE + kb) * ksgn;
}

void dfs(int cntNum)
{
    if (cntNum == num)
    {
        long long int cntAns = 0;
        for (map<long long int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
        {
            cntAns += (1ll * (it -> second) * (it -> second - 1)) >> 1;
        }
        ans = max(ans, cntAns);
        return;
    }


    int i = 0;
    while (cntState[i])
        i++;

    for (int j = i + 1; j < num; j++)
    {
        if (cntState[j])
            continue;

        int cntKa = arr[i].y - arr[j].y;
        int cntKb = arr[i].x - arr[j].x;
        int cntKsgn = 1;

        if ((cntKa > 0) != (cntKb > 0))
            cntKsgn = -1;

        cntKa = abs(cntKa);
        cntKb = abs(cntKb);

        if (cntKb == 0)
        {
            cntKsgn = 1;
            cntKa = 1;
        }
        else if (cntKa == 0)
        {
            cntKsgn = 1;
            cntKb = 0;
        }

        if (cntKa != 0 && cntKb != 0)
        {
            int gcd = __gcd(cntKa, cntKb);
            cntKa /= gcd;
            cntKb /= gcd;
        }

        long long int id = getId(cntKa, cntKb, cntKsgn);
        mp[id]++;
        cntState[i] = true;
        cntState[j] = true;
        dfs(cntNum + 2);
        mp[id]--;
        cntState[i] = false;
        cntState[j] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> num)
    {
        memset(cntState, false, sizeof(cntState));
        mp.clear();
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].x >> arr[i].y;
        }

        ans = 0;
        dfs(0);
        cout << ans << endl;
    }

    return 0;
}