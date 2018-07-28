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

typedef struct _TreapNode
{
    pair<int, int> value;
    int weight;
    int size;
    int leftSon, rightSon;
} TreapNode;

TreapNode treap[SIZE];
int treapPt, rootPt;

void update(int cntPt)
{
    treap[cntPt].size = treap[treap[cntPt].leftSon].size + treap[treap[cntPt].rightSon].size + 1;
}

int newNode(pair<int, int> val)
{
    treapPt++;
    treap[treapPt].size = 1;
    treap[treapPt].value = val;
    treap[treapPt].weight = rand();
    treap[treapPt].leftSon = 0;
    treap[treapPt].rightSon = 0;
    return treapPt;
}

int merge(int fst, int snd)
{
    if (!fst)
        return snd;
    if (!snd)
        return fst;

    if (treap[fst].weight < treap[snd].weight)
    {
        treap[fst].rightSon = merge(treap[fst].rightSon, snd);
        update(fst);
        return fst;
    }
    else
    {
        treap[snd].leftSon = merge(fst, treap[snd].leftSon);
        update(snd);
        return snd;
    }
}

void split(int cntPt, int val, int & fst, int & snd)
{
    if (!cntPt)
    {
        fst = 0;
        snd = 0;
        return;
    }

    if (treap[cntPt].value.first <= val)
    {
        fst = cntPt;
        split(treap[cntPt].rightSon, val, treap[cntPt].rightSon, snd);
    }
    else
    {
        snd = cntPt;
        split(treap[cntPt].leftSon, val, fst, treap[cntPt].leftSon);
    }
    update(cntPt);
}

int findValByRank(int cntPt, int rnk)
{
    if (rnk <= 0)
        return 0;

    while (true)
    {
        if (rnk <= treap[treap[cntPt].leftSon].size)
            cntPt = treap[cntPt].leftSon;
        else if (rnk == treap[treap[cntPt].leftSon].size + 1)
            return cntPt;
        else
        {
            rnk -= treap[treap[cntPt].leftSon].size + 1;
            cntPt = treap[cntPt].rightSon;
        }
    }

    return -1;
}

void insertNode(pair<int, int> val)
{
    int fst = 0, snd = 0;
    split(rootPt, val.first, fst, snd);
    rootPt = merge(merge(fst, newNode(val)), snd);
}

void deleteNodeAll(int val)
{
    int fst = 0, snd = 0, thd = 0;
    split(rootPt, val, fst, snd);
    split(fst, val - 1, fst, thd);
    rootPt = merge(fst, snd);
}

void deleteNode(int val)
{
    int fst = 0, snd = 0, thd = 0;
    split(rootPt, val, fst, snd);
    split(fst, val - 1, fst, thd);
    thd = merge(treap[thd].leftSon, treap[thd].rightSon);
    rootPt = merge(merge(fst, thd), snd);
}

int queryRank(int val)
{
    int fst = 0, snd = 0;
    split(rootPt, val - 1, fst, snd);
    int ans = treap[fst].size + 1;
    rootPt = merge(fst, snd);
    return ans;
}

pair<int, int> queryPrev(int val)
{
    int fst = 0, snd = 0;
    split(rootPt, val - 1, fst, snd);
    int ansPt = findValByRank(fst, treap[fst].size);
    pair<int, int> ans = treap[ansPt].value;
    rootPt = merge(fst, snd);
    return ans;
}

pair<int, int> queryNext(int val)
{
    int fst = 0, snd = 0;
    split(rootPt, val, fst, snd);
    int ansPt = findValByRank(snd, 1);
    pair<int, int> ans = treap[ansPt].value;
    rootPt = merge(fst, snd);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    srand(time(NULL));
    int qNum;
    while (cin >> qNum)
    {
        if (qNum == 0)
            break;

        treap[0].leftSon = 0;
        treap[0].rightSon = 0;
        treap[0].size = 0;
        treap[0].value = make_pair(0, -1);
        treapPt = 0;
        rootPt = 0;
        
        insertNode(make_pair(1000000000, 1));
        for (int i = 0; i < qNum; i++)
        {
            int id, val;
            cin >> id >> val;
            insertNode(make_pair(val, id));

            cout << id << " ";

            pair<int, int> pre = queryPrev(val);
            pair<int, int> nxt = queryNext(val);

            if (pre.second != -1 && abs(pre.first - val) <= abs(nxt.first - val))
                cout << pre.second << endl;
            else
                cout << nxt.second << endl;
        }
    }
    return 0;
}