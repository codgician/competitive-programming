#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

class LinkCutTree {
public:
    int sum; bool revLazy;
    int father, son[2];
};

LinkCutTree lct[SIZE];
stack<int> stk; 

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
    node(rt).sum = 1;
    for (int i = 0; i < 2; i++)
        if (node(rt).son[i] != 0)
            node(rt).sum += node(node(rt).son[i]).sum;
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
    stk.push(cntPt);
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

void link(int from, int to) {
    if (root(from) == root(to))
        return;
    evert(to);
    node(to).father = from;
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
    return node(to).sum;
}

int fac[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum; cin >> vertexNum;
    fill(lct + 0, lct + vertexNum + 2, LinkCutTree{0, 0, 0, {0, 0}});

    auto flick = [vertexNum](int i) -> int {
        return min(vertexNum + 1, i + fac[i]);
    };

    for (int i = 1; i <= vertexNum; i++) {
        cin >> fac[i];
        link(i, flick(i));
    }

    int qNum; cin >> qNum;
    while (qNum--) {
        int op, pt; cin >> op >> pt; pt++;
        if (op == 1) {   // Query
            cout << query(pt, vertexNum + 1) - 1 << '\n';
        } else {    // Modify 
            cut(pt, flick(pt));
            cin >> fac[pt];
            link(pt, flick(pt));
        }
    }

    return 0;
}