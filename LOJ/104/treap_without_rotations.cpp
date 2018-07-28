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
    int value;
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

int newNode(int val)
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

    if (treap[cntPt].value <= val)
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
}

void insertNode(int val)
{
    int fst = 0, snd = 0;
    split(rootPt, val, fst, snd);
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

int queryPrev(int val)
{
    int fst = 0, snd = 0;
    split(rootPt, val - 1, fst, snd);
    int ans = treap[findValByRank(fst, treap[fst].size)].value;
    rootPt = merge(fst, snd);
    return ans;
}

int queryNext(int val)
{
    int fst = 0, snd = 0;
    split(rootPt, val, fst, snd);
    int ans = treap[findValByRank(snd, 1)].value;
    rootPt = merge(fst, snd);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    srand(time(NULL));
    rootPt = 0;
    treapPt = 0;

    // Initialize blank node
    memset(&treap[0], 0, sizeof(TreapNode));

    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        int opr, cnt;
        cin >> opr >> cnt;

        if (opr == 1)
            insertNode(cnt);
        else if (opr == 2)
            deleteNode(cnt);
        else if (opr == 3)
            cout << queryRank(cnt) << endl;
        else if (opr == 4)
            cout << treap[findValByRank(rootPt, cnt)].value << endl;
        else if (opr == 5)
            cout << queryPrev(cnt) << endl;
        else if (opr == 6)
            cout << queryNext(cnt) << endl; 
    }
    return 0;
}
