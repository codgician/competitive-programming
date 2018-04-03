#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define K_MAX 10
#define SIZE 50010
using namespace std;

typedef struct _SegTree
{
    int leftPt, rightPt;
    int val[55];
} SegTree;

SegTree segTree[SIZE << 2];
long long int arr[SIZE];

map<pair<int ,int>, int> mp;

void build(int segTreePt, int leftPt, int rightPt)
{
    segTree[segTreePt].leftPt = leftPt;
    segTree[segTreePt].rightPt = rightPt;

    if (leftPt == rightPt)
    {
        memset(segTree[segTreePt].val, 0, sizeof(segTree[segTreePt].val));
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build((segTreePt << 1) + 1, leftPt, midPt);
    build((segTreePt << 1) + 2, midPt + 1, rightPt);

    memset(segTree[segTreePt].val, 0, sizeof(segTree[segTreePt].val));
}

void add(int segTreePt, int cntPt, int val, int typeId)
{
    if (segTree[segTreePt].leftPt == segTree[segTreePt].rightPt)
    {
        segTree[segTreePt].val[typeId] += val;
        return;
    }

    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (cntPt <= midPt)
    {
        add((segTreePt << 1) + 1, cntPt, val, typeId);
    }
    else
    {
        add((segTreePt << 1) + 2, cntPt, val, typeId);
    }

    segTree[segTreePt].val[typeId] = segTree[(segTreePt << 1) + 1].val[typeId] + segTree[(segTreePt << 1) + 2].val[typeId];
}

int query(int segTreePt, int leftPt, int rightPt)
{
    if (segTree[segTreePt].leftPt >= leftPt && segTree[segTreePt].rightPt <= rightPt)
    {
        int ans = 0;
        for (int i = 1; i <= K_MAX; i++)
        {
            int typeId = mp[make_pair(i, rightPt % i)];
            ans += segTree[segTreePt].val[typeId];
        }
        return ans;
    }

    int ans = 0;
    int midPt = (segTree[segTreePt].leftPt + segTree[segTreePt].rightPt) >> 1;
    if (leftPt <= midPt)
    {
        ans += query((segTreePt << 1) + 1, leftPt, rightPt);
    }
    if (rightPt > midPt)
    {
        ans += query((segTreePt << 1) + 2, leftPt, rightPt);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);

    int cntId = 0;
    for (int i = 1; i <= K_MAX; i++)
    {
        for (int j = 0; j < i; j++)
        {
            mp[make_pair(i, j)] = cntId++;
        }
    }

    int n;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        build(0, 0, n - 1);

        int oprNum;
        cin >> oprNum;
        while (oprNum--)
        {
            int opr;
            cin >> opr;

            if (opr == 1)
            {
                int leftPt, rightPt, k, val;
                cin >> leftPt >> rightPt >> k >> val;

                leftPt--;
                rightPt--;

                int typeId = mp[make_pair(k, leftPt % k)];

                add(0, leftPt, val, typeId);
                if (rightPt < n - 1)
                {
                    add(0, rightPt + 1, -val, typeId);
                }
            }
            else if (opr == 2)
            {
                int cntPt;
                cin >> cntPt;
                cntPt--;

                long long int ans = arr[cntPt] + query(0, 0, cntPt);
                cout << ans << endl;
            }
        }
    }
    return 0;
}
