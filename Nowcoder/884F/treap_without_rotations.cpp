#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

typedef struct _Treap {
    int val, maxv;
    int rnd, siz;
    int son[2];
} Treap;

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
    node(rt).maxv = max({node(rt).val, lson(rt).maxv, rson(rt).maxv});
}

int newNode(int val) {
    trp[trpPt] = {val, val, rand(), 1, {0, 0}};
    return trpPt++;
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

int queryByRank(int rt, int k) {
    int fstRt = 0, sndRt = 0, thdRt = 0;
    split(rt, k - 1, fstRt, sndRt);
    split(sndRt, 1, sndRt, thdRt);
    int ret = node(sndRt).val;
    rt = merge(fstRt, merge(sndRt, thdRt));
    return ret;
}

int queryLen(int rt, int val) {
    if (rt == 0)
        return 0;
    if (lson(rt).maxv > val)
        return queryLen(node(rt).son[0], val);
    if (node(rt).val > val)
        return lson(rt).siz;
    return queryLen(node(rt).son[1], val) + lson(rt).siz + 1; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    srand(19260817);
    trpPt = 0; trp[trpPt++] = {INT_MIN, INT_MIN, 0, 0, {0, 0}};

    int rt = 0;
    int len, qNum; cin >> len >> qNum;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        rt = merge(rt, newNode(cnt));
    }

    while (qNum--) {
        int op; cin >> op;
        if (op == 1) {
            int leftPt, midPt, rightPt;
            cin >> leftPt >> midPt >> rightPt;
            int remRt = 0, fstRt = 0, sndRt = 0;
            split(rt, rightPt, rt, remRt);
            split(rt, midPt, fstRt, sndRt); rt = 0;

            while (fstRt != 0 && sndRt != 0) {
                int fst = queryByRank(fstRt, 1), snd = queryByRank(sndRt, 1);
                if (fst > snd)
                    swap(fst, snd), swap(fstRt, sndRt);
                int len = queryLen(fstRt, snd);
                int orz = 0; split(fstRt, len, orz, fstRt);
                rt = merge(rt, orz);
            }

            rt = merge(rt, fstRt);
            rt = merge(rt, sndRt);
            rt = merge(rt, remRt);
        } else {
            int pos; cin >> pos;
            cout << queryByRank(rt, pos) << '\n';
        }
    }

    return 0;
}