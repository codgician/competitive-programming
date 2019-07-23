#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _TreapNode {
    int val, key, siz;
    int leftSon, rightSon;
} TreapNode;

TreapNode treap[SIZE]; int treapPt;

void update(int cntPt) {
    treap[cntPt].siz = treap[treap[cntPt].leftSon].siz + treap[treap[cntPt].rightSon].siz + 1;
}

int newNode(int val) {
    treap[++treapPt] = {val, rand(), 1, 0, 0};
    return treapPt;
}

int merge(int fstRt, int sndRt) {
    if (fstRt == 0)
        return sndRt;
    if (sndRt == 0)
        return fstRt;

    if (treap[fstRt].key < treap[sndRt].key) {
        treap[fstRt].rightSon = merge(treap[fstRt].rightSon, sndRt);
        update(fstRt); return fstRt;
    }

    treap[sndRt].leftSon = merge(fstRt, treap[sndRt].leftSon);
    update(sndRt); return sndRt;
}

void split(int cntPt, int val, int& fstRt, int& sndRt) {
    if (!cntPt) {
        fstRt = 0; sndRt = 0;
        return;
    }

    if (treap[cntPt].val <= val) {
        fstRt = cntPt;
        split(treap[cntPt].rightSon, val, treap[cntPt].rightSon, sndRt);
    } else {
        sndRt = cntPt;
        split(treap[cntPt].leftSon, val, fstRt, treap[cntPt].leftSon);
    }

    update(cntPt);
}

int findValByRank(int cntPt, int rnk) {
    while (true) {
        if (rnk == treap[treap[cntPt].leftSon].siz + 1)
            return cntPt;
        if (rnk <= treap[treap[cntPt].leftSon].siz) {
            cntPt = treap[cntPt].leftSon;
        } else {
            rnk -= treap[treap[cntPt].leftSon].siz + 1;
            cntPt = treap[cntPt].rightSon;
        }
    }
}

void insertNode(int & cntRt, int val) {
    int fstRt = 0, sndRt = 0;
    split(cntRt, val, fstRt, sndRt);
    cntRt = merge(merge(fstRt, newNode(val)), sndRt);
}

void deleteNodeAll(int & cntRt, int val) {
    int fstRt = 0, sndRt = 0, thdRt = 0;
    split(cntRt, val, fstRt, sndRt);
    split(fstRt, val - 1, fstRt, thdRt);
    cntRt = merge(fstRt, sndRt);
}

void deleteNode(int & cntRt, int val) {
    int fstRt = 0, sndRt = 0, thdRt = 0;
    split(cntRt, val, fstRt, sndRt);
    split(fstRt, val - 1, fstRt, thdRt);
    thdRt = merge(treap[thdRt].leftSon, treap[thdRt].rightSon);
    cntRt = merge(merge(fstRt, thdRt), sndRt);
}

int queryRank(int & cntRt, int val) {
    int fstRt = 0, sndRt = 0;
    split(cntRt, val - 1, fstRt, sndRt);
    int ret = treap[fstRt].siz + 1;
    cntRt = merge(fstRt, sndRt);
    return ret;
}

int queryPrev(int & cntRt, int val) {
    int fstRt = 0, sndRt = 0;
    split(cntRt, val - 1, fstRt, sndRt);
    int ret = treap[findValByRank(fstRt, treap[fstRt].siz)].val;
    cntRt = merge(fstRt, sndRt);
    return ret;
}

int queryNext(int & cntRt, int val) {
    int fstRt = 0, sndRt = 0;
    split(cntRt, val, fstRt, sndRt);
    int ret = treap[findValByRank(sndRt, 1)].val;
    cntRt = merge(fstRt, sndRt);
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); srand(time(NULL));
    int cntRt = 0; treapPt = 0;

    treap[0] = {0, 0, 0, 0, 0};

    int qNum; cin >> qNum;
    while (qNum--) {
        int op, cnt; cin >> op >> cnt;
        if (op == 1)
            insertNode(cntRt, cnt);
        else if (op == 2)
            deleteNode(cntRt, cnt);
        else if (op == 3)
            cout << queryRank(cntRt, cnt) << '\n';
        else if (op == 4)
            cout << treap[findValByRank(cntRt, cnt)].val << '\n';
        else if (op == 5)
            cout << queryPrev(cntRt, cnt) << '\n';
        else if (op == 6)
            cout << queryNext(cntRt, cnt) << '\n';
    }
    return 0;
}