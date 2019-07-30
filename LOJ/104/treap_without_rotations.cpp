#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
uniform_int_distribution<int> unifInt;

class Treap {
public:
    int val, rnd, siz;
    int son[2];
};

Treap trp[SIZE]; int trpPt;

const auto node = [](int rt) -> Treap & {
    return trp[rt];
};

const auto lson = [](int rt) -> Treap & {
    return trp[trp[rt].son[0]];
};

const auto rson = [](int rt) -> Treap & {
    return trp[trp[rt].son[1]];
};

void maintain(int rt) {
    node(rt).siz = lson(rt).siz + rson(rt).siz + 1;
}

vector<int> vec;

int newNode(int val) {
    int cntPt = trpPt++;
    if (vec.size()) {
        cntPt = vec.back();
        vec.pop_back(); trpPt--;
    }
    trp[cntPt] = {val, unifInt(rng), 1, {0, 0}};
    return cntPt;
}

int merge(int fstRt, int sndRt) {
    if (fstRt == 0)
        return sndRt;
    if (sndRt == 0)
        return fstRt;

    if (node(fstRt).rnd < node(sndRt).rnd) {
        node(fstRt).son[1] = merge(node(fstRt).son[1], sndRt);
        maintain(fstRt); return fstRt;
    } else {
        node(sndRt).son[0] = merge(fstRt, node(sndRt).son[0]);
        maintain(sndRt); return sndRt;
    }
}

void split(int rt, int k, int & fstRt, int & sndRt) {
    if (rt == 0) {
        fstRt = 0; sndRt = 0;
        return;
    }

    if (k <= lson(rt).siz) {
        sndRt = rt; split(node(rt).son[0], k, fstRt, node(rt).son[0]);
    } else {
        fstRt = rt; split(node(rt).son[1], k - lson(rt).siz - 1, node(rt).son[1], sndRt);
    }
    maintain(rt);
}

void splitByVal(int rt, int val, int & fstRt, int & sndRt) {
    if (rt == 0) {
        fstRt = 0; sndRt = 0;
        return;
    }

    if (node(rt).val > val)
        sndRt = rt, splitByVal(node(rt).son[0], val, fstRt, node(rt).son[0]);
    else
        fstRt = rt, splitByVal(node(rt).son[1], val, node(rt).son[1], sndRt);        
    maintain(rt);
}

int queryRank(int rt, int val) {
    if (rt == 0)
        return 1;
    if (val <= node(rt).val)
        return queryRank(node(rt).son[0], val);
    return queryRank(node(rt).son[1], val) + lson(rt).siz + 1;
}

int queryByRank(int rt, int k) {
    int fstRt = 0, sndRt = 0, thdRt = 0;
    split(rt, k - 1, fstRt, sndRt);
    split(sndRt, 1, sndRt, thdRt);
    int ret = node(sndRt).val;
    rt = merge(fstRt, merge(sndRt, thdRt));
    return ret;
}

void insert(int & rt, int val) {
    int k = queryRank(rt, val);
    int fstRt = 0, sndRt = 0;
    split(rt, k - 1, fstRt, sndRt);
    rt = merge(fstRt, merge(newNode(val), sndRt));
}

void remove(int & rt, int val) {
    int k = queryRank(rt, val);
    int fstRt = 0, sndRt = 0, thdRt = 0;
    split(rt, k - 1, fstRt, sndRt); 
    split(sndRt, 1, sndRt, thdRt);
    rt = merge(fstRt, thdRt); vec.push_back(sndRt);
}

int queryPrev(int & rt, int val) {
    int fstRt = 0, sndRt = 0;
    splitByVal(rt, val - 1, fstRt, sndRt);
    int ret = queryByRank(fstRt, node(fstRt).siz);
    rt = merge(fstRt, sndRt);
    return ret;
}

int queryNext(int & rt, int val) {
    int fstRt = 0, sndRt = 0;
    splitByVal(rt, val, fstRt, sndRt);
    int ret = queryByRank(sndRt, 1);
    rt = merge(fstRt, sndRt);
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    srand(19260817); vec.clear();
    trpPt = 0; trp[trpPt++] = {0, 0, 0, {0, 0}};

    int rt = 0, qNum; cin >> qNum;
    while (qNum--) {
        int op, cnt; cin >> op >> cnt;
        if (op == 1)
            insert(rt, cnt);
        else if (op == 2)
            remove(rt, cnt);
        else if (op == 3)
            cout << queryRank(rt, cnt) << '\n';
        else if (op == 4)
            cout << queryByRank(rt, cnt) << '\n';
        else if (op == 5)
            cout << queryPrev(rt, cnt) << '\n';
        else if (op == 6)
            cout << queryNext(rt, cnt) << '\n';
    }

    return 0;
}
