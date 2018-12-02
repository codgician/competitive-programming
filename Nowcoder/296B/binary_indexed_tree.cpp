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

long long int bitArr[2][SIZE];
int arr[SIZE], len;

vector<pair<int, int> > qArr[2];

int getLowbit(int n)
{
    return n & (-n);
}

void add(int id, int pos, int val)
{
    for (int i = pos; i <= len + 1; i += getLowbit(i))
    {
        bitArr[id][i] += val;
    }
}

long long int prefixSum(int id, int pos)
{
    long long int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[id][i];
    }
    return ans;
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        scanf("%d", &len);
        for (int i = 0; i <= len + 1; i++)
        {
            bitArr[0][i] = 0;
            bitArr[1][i] = 0;
        }
        qArr[0].clear();
        qArr[1].clear();

        for (int i = 1; i <= len; i++)
        {
            int cnt;
            scanf("%d", &cnt);
            arr[cnt] = i;
        }

        for (int i = 1; i < len; i++)
        {
            int fstPt = arr[i], sndPt = arr[i + 1];
            if (fstPt > sndPt)
                swap(fstPt, sndPt);
            qArr[i & 1].push_back(make_pair(fstPt, sndPt));
        }

        bool ans = true;
        for (int i = 0; i < 2; i++)
        {
            sort(qArr[i].begin(), qArr[i].end());
            for (auto cnt : qArr[i])
            {
                if (prefixSum(i, cnt.first) != prefixSum(i, cnt.second))
                {
                    ans = false;
                    break;
                }
                add(i, cnt.first, 1);
                add(i, cnt.second + 1, -1);
            }
            if (!ans)
                break;
        }

        if (ans)
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}