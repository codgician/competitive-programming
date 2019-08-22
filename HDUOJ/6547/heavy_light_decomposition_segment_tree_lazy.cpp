#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;

int father[SIZE], depth[SIZE], siz[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;
long long int val[SIZE];

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

/* Segment Tree */

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt, zeroNum;
    long long int minv, maxv, sum, lazy;
} SegNode;
SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    SegNode & cntNode = segTree[segPt], & leftNode = segTree[LEFT_SON], & rightNode = segTree[RIGHT_SON];
    cntNode.sum = leftNode.sum + rightNode.sum;
    cntNode.zeroNum = leftNode.zeroNum + rightNode.zeroNum;
    cntNode.minv = min(leftNode.minv, rightNode.minv);
    cntNode.maxv = max(leftNode.maxv, rightNode.maxv);
}

void pushDown(int segPt) {
    SegNode & cntNode = segTree[segPt];
    if (cntNode.lazy == -1)
        return;
    SegNode & leftNode = segTree[LEFT_SON], & rightNode = segTree[RIGHT_SON];

    leftNode.minv = cntNode.lazy; rightNode.minv = cntNode.lazy;
    leftNode.maxv = cntNode.lazy; rightNode.maxv = cntNode.lazy;
    leftNode.sum = cntNode.lazy * (leftNode.rightPt - leftNode.leftPt + 1 - leftNode.zeroNum);
    rightNode.sum = cntNode.lazy * (rightNode.rightPt - rightNode.leftPt + 1 - rightNode.zeroNum);
    leftNode.lazy = cntNode.lazy; rightNode.lazy = cntNode.lazy;

    cntNode.lazy = -1;
}

void build(int segPt, int leftPt, int rightPt) {
    SegNode & cntNode = segTree[segPt];

    cntNode.leftPt = leftPt; cntNode.rightPt = rightPt;
    cntNode.lazy = -1;
    if (leftPt == rightPt) {
        long long int cnt = val[orig[leftPt]];
        cntNode.sum = cnt;
        cntNode.minv = max(1ll, cnt);
        cntNode.maxv = max(1ll, cnt);
        cntNode.zeroNum = (cnt == 0);
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeSqrt(int segPt, int qLeftPt, int qRightPt) {
    SegNode & cntNode = segTree[segPt];
    if (cntNode.leftPt >= qLeftPt && cntNode.rightPt <= qRightPt) {
        long long int minSqrt = sqrt(cntNode.minv), maxSqrt = sqrt(cntNode.maxv);
        if (minSqrt == maxSqrt) {
            cntNode.sum = minSqrt * (cntNode.rightPt - cntNode.leftPt + 1 - cntNode.zeroNum);
            cntNode.minv = minSqrt; cntNode.maxv = minSqrt; cntNode.lazy = minSqrt;
            return;
        }
    }

    pushDown(segPt);
    int midPt = (cntNode.leftPt + cntNode.rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeSqrt(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        rangeSqrt(RIGHT_SON, qLeftPt, qRightPt);
    pushUp(segPt);
}

long long int rangeSum(int segPt, int qLeftPt, int qRightPt) {
    SegNode & cntNode = segTree[segPt];
    if (cntNode.leftPt >= qLeftPt && cntNode.rightPt <= qRightPt) 
        return cntNode.sum;
    
    pushDown(segPt);
    long long int ret = 0;
    int midPt = (cntNode.leftPt + cntNode.rightPt) >> 1;
    if (qLeftPt <= midPt)
        ret += rangeSum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ret += rangeSum(RIGHT_SON, qLeftPt, qRightPt);
    return ret;
}

void dfs1(int cntPt) {
    siz[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (depth[nextPt] != -1)
            continue;
        father[nextPt] = cntPt;
        depth[nextPt] = depth[cntPt] + 1;
        dfs1(nextPt);
        siz[cntPt] += siz[nextPt];
        if (hson[cntPt] == -1 || siz[nextPt] > siz[hson[cntPt]])
            hson[cntPt] = nextPt;
    }
}

void dfs2(int cntPt, int cntTop) {
    top[cntPt] = cntTop;
    id[cntPt] = ++cntId;
    orig[cntId] = cntPt;
    if (hson[cntPt] == -1)
        return;
    dfs2(hson[cntPt], cntTop);

    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == hson[cntPt] || nextPt == father[cntPt])
            continue;
        dfs2(nextPt, nextPt);
    }
}


long long int queryRoute(int fstPt, int sndPt) {
    long long int ans = 0;
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        ans += rangeSum(1, id[top[fstPt]], id[fstPt]);
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    ans += rangeSum(1, id[fstPt], id[sndPt]);
    return ans;
}

void updateRoute(int fstPt, int sndPt) {
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        rangeSqrt(1, id[top[fstPt]], id[fstPt]);
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    rangeSqrt(1, id[fstPt], id[sndPt]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, qNum;
    while (cin >> vertexNum >> qNum) {
        for (int i = 0; i < vertexNum; i++)
            cin >> val[i], head[i] = -1;
        edgePt = 0;
        for (int i = 1; i < vertexNum; i++) {
            int from, to; cin >> from >> to;
            from--; to--;
            addEdge(from, to);
            addEdge(to, from);
        }

        memset(depth, -1, sizeof(depth));
        memset(hson, -1, sizeof(hson));
        father[0] = 0, depth[0] = 0; cntId = 0;
        dfs1(0); dfs2(0, 0);
        build(1, 1, vertexNum);

        while (qNum--) {
            int op, from, to;
            cin >> op >> from >> to;
            from--; to--;
            if (op == 0)
                updateRoute(from, to);
            else
                cout << queryRoute(from, to) << '\n';
        }
    }

    return 0;
}