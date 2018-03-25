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
#define SIZE 200010
using namespace std;

int parent[SIZE], memberNum[SIZE];
int bitArr[SIZE];
int nodeNum, bitSize;

int getLowbit(int n)
{
    return n & (-n);
}

void add(int pos, int val)
{
    for (int i = pos; i <= nodeNum; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int findK(int k)
{
    int cnt = 0, ans = 0;
    for (int i = 1 << 18; i > 0; i >>= 1)
    {
        ans += i;
        if (ans >= nodeNum || cnt + bitArr[ans] >= k)
            ans -= i;
        else
            cnt += bitArr[ans];
    }
    return ans + 1;
}

int getParent(int i)
{
    int rootNode = i;
    while (rootNode != parent[rootNode])
        rootNode = parent[rootNode];
    int cntNode = rootNode;
    while (cntNode != rootNode)
    {
        int tmp = parent[cntNode];
        parent[cntNode] = rootNode;
        cntNode = tmp;
    }
    return rootNode;
}

void mergeNode(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        parent[bParent] = aParent;

        add(memberNum[aParent], -1);
        add(memberNum[bParent], -1);
        memberNum[aParent] += memberNum[bParent];
        add(memberNum[aParent], 1);
        memberNum[bParent] = 0;

        bitSize--;
    }
}

int main()
{
    memset(bitArr, 0, sizeof(bitArr));
    int oprNum;
    scanf("%d%d", &nodeNum, &oprNum);

    for (int i = 0; i < nodeNum; i++)
    {
        parent[i] = i;
        memberNum[i] = 1;
    }
    add(1, nodeNum);
    bitSize = nodeNum;

    while (oprNum--)
    {
        int opr;
        scanf("%d", &opr);
        if (opr == 0)
        {
            int fst, snd;
            scanf("%d%d", &fst, &snd);
            fst--;
            snd--;
            mergeNode(fst, snd);
        }
        else
        {
            int k;
            scanf("%d", &k);
            printf("%d\n", findK(bitSize - k + 1));
        }
    }
    return 0;
}


