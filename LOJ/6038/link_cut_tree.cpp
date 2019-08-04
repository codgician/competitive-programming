#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

/* Disjoint Set */

int parent[SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return cntPt;
    parent[cntPt] = getParent(parent[cntPt]);
    return parent[cntPt];
}

void merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return;
    parent[sndPt] = fstPt;
}

/* Link/cut tree */

class LinkCutTree {
public:
    int siz, fstPt, sndPt; bool revLazy;
    int father, son[2];
};

LinkCutTree lct[SIZE];

const auto node = [](int rt) -> LinkCutTree & {
    return lct[rt];
};
const auto father = [](int rt) -> LinkCutTree & {
    return lct[node(rt).father];
};
const auto lson = [](int rt) -> LinkCutTree & {
    return lct[node(rt).son[0]];
};
const auto rson = [](int rt) -> LinkCutTree & {
    return lct[node(rt).son[1]];
};

void pushUp(int rt) {
    node(rt).siz = 1;
    for (int i = 0; i < 2; i++)
        if (node(rt).son[i] != 0)
            node(rt).siz += node(node(rt).son[i]).siz;
}

void pushDown(int rt) {
    if (!node(rt).revLazy)
        return;
    swap(node(rt).son[0], node(rt).son[1]);
    for (int i = 0; i < 2; i++)
        if (node(rt).son[i] != 0)
            node(node(rt).son[i]).revLazy ^= 1;
    node(rt).revLazy = false;
}

bool isRoot(int cntPt) {
    return father(cntPt).son[0] != cntPt && father(cntPt).son[1] != cntPt;
}

int whichSon(int cntPt) {
    return father(cntPt).son[1] == cntPt;
}

void rotate(int cntPt) {
    int fatherPt = node(cntPt).father, grandPt = node(fatherPt).father;
    int sonPt = node(cntPt).son[whichSon(cntPt) ^ 1];

    if (!isRoot(fatherPt))
        node(grandPt).son[whichSon(fatherPt)] = cntPt;
    if (whichSon(cntPt) == 0)
        node(cntPt).son[1] = fatherPt, node(fatherPt).son[0] = sonPt;
    else
        node(cntPt).son[0] = fatherPt, node(fatherPt).son[1] = sonPt;
    node(cntPt).father = grandPt;
    node(fatherPt).father = cntPt;
    if (sonPt != 0)
        node(sonPt).father = fatherPt;
    pushUp(fatherPt);
}

void splay(int cntPt) {
    stack<int> stk; stk.push(cntPt);
    while (!isRoot(stk.top()))
        stk.push(node(stk.top()).father);
    while (stk.size())
        pushDown(stk.top()), stk.pop();
    while (!isRoot(cntPt)) {
        if (!isRoot(node(cntPt).father))
            rotate(whichSon(cntPt) == whichSon(node(cntPt).father) ? node(cntPt).father : cntPt);
        rotate(cntPt);
    }
    pushUp(cntPt);
}

void expose(int cntPt) {
    int sonPt = 0;
    while (cntPt != 0) {
        splay(cntPt);
        node(cntPt).son[1] = sonPt;
        pushUp(cntPt);
        sonPt = cntPt;
        cntPt = node(cntPt).father;
    }
}

void evert(int cntPt) {
    expose(cntPt);
    splay(cntPt);
    node(cntPt).revLazy ^= 1;
}

int root(int cntPt) {
    expose(cntPt);
    splay(cntPt);
    while (node(cntPt).son[0] != 0) {
        pushDown(cntPt);
        cntPt = node(cntPt).son[0];
    }
    splay(cntPt);
    return cntPt;
}

void cut(int from, int to) {
    evert(from);
    expose(to);
    splay(to);
    if (node(to).son[0] == from) {
        node(to).son[0] = 0;
        node(from).father = 0;
    }
}

int query(int from, int to) {
    evert(from);
    expose(to);
    splay(to);
    return node(to).siz;
}

void link(int from, int to) {
    if (root(from) == root(to))
        return;
    evert(to); node(to).father = from;

    // Consider 6 cases
    int fromParent = getParent(from), toParent = getParent(to);
    array<pair<int, int>, 6> cases = {
        make_pair(node(fromParent).fstPt, node(fromParent).sndPt),
        make_pair(node(fromParent).fstPt, node(toParent).fstPt),
        make_pair(node(fromParent).fstPt, node(toParent).sndPt),
        make_pair(node(fromParent).sndPt, node(toParent).fstPt),
        make_pair(node(fromParent).sndPt, node(toParent).sndPt),
        make_pair(node(toParent).fstPt, node(toParent).sndPt)
    };

    int maxv = -1, fstPt = -1, sndPt = -1;
    for (const auto & p : cases) {
        int cnt = query(p.first, p.second);
        if (maxv < cnt)
            maxv = cnt, fstPt = p.first, sndPt = p.second;
    }

    merge(toParent, fromParent);
    node(toParent).fstPt = fstPt; node(toParent).sndPt = sndPt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int type, vertexNum, qNum, lastAns = 0;
    cin >> type >> vertexNum >> qNum;

    fill(lct + 0, lct + vertexNum + 1, LinkCutTree{1, 0, 0, false, 0, {0, 0}});
    for (int i = 1; i <= vertexNum; i++)
        parent[i] = i, lct[i].fstPt = i, lct[i].sndPt = i;

    for (int t = 0; t < qNum; t++) {
        int op; cin >> op;
        if (op == 1) {
            int from, to; cin >> from >> to;
            from ^= lastAns; to ^= lastAns;
            link(from, to);
        } else {
            int cntPt; cin >> cntPt; cntPt ^= lastAns;
            int parentPt = getParent(cntPt); 
            lastAns = max(query(cntPt, lct[parentPt].fstPt), query(cntPt, lct[parentPt].sndPt)) - 1;
            cout << lastAns << '\n';
            lastAns *= type;
        }
    }

    return 0;
}