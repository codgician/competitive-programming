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

#define SIZE 50010

typedef struct _TreeNode
{
    int parent;
    int leftSon, rightSon;
    int id, key, value;
} TreeNode;

typedef struct _Ans
{
    int id;
    int parent, leftSon, rightSon;
} Ans;

TreeNode treeArr[SIZE];
Ans ansArr[SIZE];
int stk[SIZE];

bool cmpKey(TreeNode fst, TreeNode snd)
{
    return fst.key < snd.key;
}

bool cmpId(Ans fst, Ans snd)
{
    return fst.id < snd.id;
}

void build(int len)
{
    stack<int> stk;
    for(int i = 0; i < len; ++i)
    {
        int lastPop = -1;
        while (!stk.empty() && treeArr[stk.top()].value > treeArr[i].value)
        {
            lastPop = stk.top();
            stk.pop();
        }

        if (!stk.empty())
        {
            treeArr[i].parent = stk.top();
            treeArr[stk.top()].rightSon = i;
        }

        if (lastPop != -1)
        {
            treeArr[lastPop].parent = i;
            treeArr[i].leftSon = lastPop;
        }

        stk.push(i);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int num;
    while (cin >> num)
    {
        for (int i = 0; i < num; i++)
        {
            cin >> treeArr[i].key >> treeArr[i].value;
            treeArr[i].id = i + 1;
            treeArr[i].leftSon = -1;
            treeArr[i].rightSon = -1;
            treeArr[i].parent = -1;
        }

        sort(treeArr + 0, treeArr + num, cmpKey);

        build(num);

        for (int i = 0; i < num; i++)
        {
            ansArr[i] = {
                treeArr[i].id,
                (treeArr[i].parent == -1 ? 0 : treeArr[treeArr[i].parent].id),
                (treeArr[i].leftSon == -1 ? 0 : treeArr[treeArr[i].leftSon].id),
                (treeArr[i].rightSon == -1 ? 0 : treeArr[treeArr[i].rightSon].id)
            };
        }

        sort(ansArr + 0, ansArr + num, cmpId);

        cout << "YES" << endl;
        for (int i = 0; i < num; i++)
        {
            cout << ansArr[i].parent << " " << ansArr[i].leftSon << " " << ansArr[i].rightSon << endl;
        }
    }
    return 0;
}