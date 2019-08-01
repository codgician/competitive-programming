#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

class LinkCutTree {
public:
    int val, maxv, maxPt; bool revLazy;
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
    node(rt).maxv = node(rt).val; node(rt).maxPt = rt;
    for (int i = 0; i < 2; i++)
        if (node(rt).son[i] != 0)
            if (node(rt).maxv < node(node(rt).son[i]).maxv)
                node(rt).maxv = node(node(rt).son[i]).maxv, node(rt).maxPt = node(node(rt).son[i]).maxPt;
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

pair<int, int> query(int from, int to) {
    evert(from);
    expose(to);
    splay(to);
    return make_pair(node(to).maxv, node(to).maxPt);
}

void update(int cntPt, int val) {
    splay(cntPt);
    node(cntPt).val = val;
    pushUp(cntPt);
}

class Edge {
public:
    int from, to, fst, snd;
    bool operator < (const Edge & snd) const {
        return this -> fst < snd.fst;
    }
};

Edge edge[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int vertexNum, edgeNum;
    cin >> vertexNum >> edgeNum;
    fill(lct + 0, lct + vertexNum + edgeNum + 1, LinkCutTree{0, 0, 0, 0, 0, {0, 0}});
    for (int i = 0; i < edgeNum; i++)
        cin >> edge[i].from >> edge[i].to >> edge[i].fst >> edge[i].snd;
    sort(edge + 0, edge + edgeNum);

    int ans = INT_MAX;
    for (int i = 0; i < edgeNum; i++) {
        Edge & e = edge[i];

        if (root(e.from) == root(e.to)) {
            auto ret = query(e.from, e.to);
            if (edge[i].snd >= ret.first)
                continue;
            cut(edge[ret.second - vertexNum - 1].from, ret.second);
            cut(ret.second, edge[ret.second - vertexNum - 1].to);
        }

        int pt = vertexNum + i + 1;
        update(pt, e.snd);
        link(e.from, pt); link(pt, e.to);
        if (root(1) == root(vertexNum))
            ans = min(ans, e.fst + query(1, vertexNum).first);
    }

    cout << (ans == INT_MAX ? -1 : ans) << '\n';
    return 0;
}
