#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], vertexNum, edgePt;

int father[SIZE], depth[SIZE], siz[SIZE], arr[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt;
    int sum, lazy;
} SegNode;
SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void pushDown(int segPt) {
    if (segTree[segPt].lazy != -1) {
        segTree[LEFT_SON].sum = segTree[segPt].lazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1);
        segTree[RIGHT_SON].sum = segTree[segPt].lazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1);

        segTree[LEFT_SON].lazy = segTree[segPt].lazy;
        segTree[RIGHT_SON].lazy = segTree[segPt].lazy;

        segTree[segPt].lazy = -1;
    }
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    if (leftPt == rightPt) {
        segTree[segPt].sum = 0;
        segTree[segPt].lazy = -1;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
    segTree[segPt].lazy = -1;
}

void rangeUpdate(int segPt, int qLeftPt, int qRightPt, int val) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        segTree[segPt].sum = val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1);
        segTree[segPt].lazy = val;
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeUpdate(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeUpdate(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

int querySum(int segPt, int qLeftPt, int qRightPt) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        return segTree[segPt].sum;
    }
    pushDown(segPt);
    int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += querySum(RIGHT_SON, qLeftPt, qRightPt);
    return ans;
}

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
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

int querySubtree(int rootPt) {
    return querySum(1, id[rootPt], id[rootPt] + siz[rootPt] - 1);
}

void updateSubtree(int rootPt, int val) {
    rangeUpdate(1, id[rootPt], id[rootPt] + siz[rootPt] - 1, val);
}

int queryRoute(int fstPt, int sndPt) {
    int ans = 0;
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        ans += querySum(1, id[top[fstPt]], id[fstPt]);
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    ans += querySum(1, id[fstPt], id[sndPt]);
    return ans;
}

void updateRoute(int fstPt, int sndPt, int val) {
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        rangeUpdate(1, id[top[fstPt]], id[fstPt], val);
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    rangeUpdate(1, id[fstPt], id[sndPt], val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0, cntId = 0;
    cin >> vertexNum;
    for (int i = 1; i < vertexNum; i++) {
        int to;
        cin >> to;
        addEdge(i, to);
        addEdge(to, i);
    }

    memset(depth, -1, sizeof(depth));
    memset(hson, -1, sizeof(hson));
    father[0] = 0, depth[0] = 0;
    dfs1(0);
    dfs2(0, 0);
    build(1, 1, vertexNum);

    int qNum;
    cin >> qNum;
    while (qNum--) {
        string opr;
        int pt;
        cin >> opr >> pt;
        if (opr[0] == 'i') {
            // Install
            cout << depth[pt] - queryRoute(0, pt) + 1 << endl;
            updateRoute(0, pt, 1);
        } else {
            // Uninstall
            cout << querySubtree(pt) << endl;
            updateSubtree(pt, 0);
        }
    }

    return 0;
}