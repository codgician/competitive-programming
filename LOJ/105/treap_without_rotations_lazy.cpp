#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
uniform_int_distribution<int> unifInt(0, 1e9);

class Treap {
public:
    int val, rnd, siz; bool lazy;
    Treap * son[2];

    Treap (int v) : val (v) {
        this -> rnd = unifInt(rng); this -> siz = 1; this -> lazy = false;
        this -> son[0] = nullptr; this -> son[1] = nullptr;
    }

    void maintain() {
        this -> siz = 1;
        for (int i = 0; i < 2; i++)
            if (this -> son[i] != nullptr)
                this -> siz += this -> son[i] -> siz;
    }

    void pushDown() {
        if (!this -> lazy)
            return;
        swap(this -> son[0], this -> son[1]);
        for (int i = 0; i < 2; i++)
            if (this -> son[i] != nullptr)
                this -> son[i] -> lazy ^= 1;
        this -> lazy = false; return;
    }
};

auto siz = [](Treap * rt) {
    return rt == nullptr ? 0 : rt -> siz;
};

Treap * merge(Treap * fstRt, Treap * sndRt) {
    if (fstRt == nullptr)
        return sndRt;
    if (sndRt == nullptr)
        return fstRt;

    if (fstRt -> rnd < sndRt -> rnd) {
        fstRt -> pushDown();
        fstRt -> son[1] = merge(fstRt -> son[1], sndRt);
        fstRt -> maintain(); return fstRt;
    } else {
        sndRt -> pushDown();
        sndRt -> son[0] = merge(fstRt, sndRt -> son[0]);
        sndRt -> maintain(); return sndRt;
    }
}

void split(Treap * rt, int k, Treap * & fstRt, Treap * & sndRt) {
    if (rt == nullptr) {
        fstRt = nullptr; sndRt = nullptr;
        return;
    }

    rt -> pushDown();
    if (k <= siz(rt -> son[0])) {
        split(rt -> son[0], k, fstRt, rt -> son[0]);
        rt -> maintain(); sndRt = rt;
    } else {
        split(rt -> son[1], k - siz(rt -> son[0]) - 1, rt -> son[1], sndRt);
        rt -> maintain(); fstRt = rt;
    }
}

int getRank(Treap * rt, int val) {
    if (rt == nullptr)
        return 0;
    if (val <= rt -> val)
        return getRank(rt -> son[0], val);
    return getRank(rt -> son[1], val) + siz(rt -> son[0]) + 1;
}

void insert(Treap * & rt, int val) {
    int k = getRank(rt, val);
    Treap * fstRt = nullptr, * sndRt = nullptr;
    split(rt, k, fstRt, sndRt);
    rt = merge(fstRt, merge(new Treap(val), sndRt));
}

void remove(Treap * & rt , int val) {
    int k = getRank(rt, val) ;
    Treap * fstRt = nullptr, * sndRt = nullptr, * thdRt = nullptr;
    split(rt, k - 1, fstRt, sndRt); 
    split(sndRt, 1, sndRt, thdRt);
    rt = merge(fstRt, thdRt); delete sndRt;
}

void reverse(Treap * & rt, int qLeftPt, int qRightPt) {
    Treap * fstRt = nullptr, * sndRt = nullptr, * thdRt = nullptr;
    split(rt, qLeftPt - 1, fstRt, sndRt); 
    split(sndRt, qRightPt - qLeftPt + 1, sndRt, thdRt);
    sndRt -> lazy = true;
    rt = merge(fstRt, merge(sndRt, thdRt));
}

void print(Treap * rt) {
    if (rt == nullptr)
        return;
    if (rt -> lazy)
        rt -> pushDown();
    print(rt -> son[0]);
    cout << rt -> val << " ";
    print(rt -> son[1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len, qNum; cin >> len >> qNum;
    Treap * rt = nullptr;
    for (int i = 1; i <= len; i++)
        insert(rt, i);
    while (qNum--) {
        int qLeftPt, qRightPt; cin >> qLeftPt >> qRightPt;
        reverse(rt, qLeftPt, qRightPt);
    }
    print(rt);
    return 0;
}