#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt, vertexNum;

int father[SIZE], depth[SIZE], siz[SIZE], arr[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;
int mod;

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt;
    int sum, lazy;
} SegNode;
SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    segTree[segPt].sum = (segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum) % mod;
}

void pushDown(int segPt) {
    if (segTree[segPt].lazy != 0) {
        segTree[LEFT_SON].sum += segTree[segPt].lazy * (segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1) % mod;
        segTree[LEFT_SON].sum %= mod;
        segTree[RIGHT_SON].sum += segTree[segPt].lazy * (segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1) % mod;
        segTree[RIGHT_SON].sum %= mod;

        segTree[LEFT_SON].lazy += segTree[segPt].lazy;
        segTree[LEFT_SON].lazy %= mod;
        segTree[RIGHT_SON].lazy += segTree[segPt].lazy;
        segTree[RIGHT_SON].lazy %= mod;

        segTree[segPt].lazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    if (leftPt == rightPt) {
        segTree[segPt].sum = arr[orig[leftPt]] % mod;
        segTree[segPt].lazy = 0;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
    segTree[segPt].lazy = 0;
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, int val) {
    if (qLeftPt > qRightPt)
        swap(qLeftPt, qRightPt);
    val %= mod;
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        segTree[segPt].sum += val * (segTree[segPt].rightPt - segTree[segPt].leftPt + 1) % mod;
        segTree[segPt].sum %= mod;
        segTree[segPt].lazy += val;
        segTree[segPt].lazy %= mod;
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeAdd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeAdd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

int querySum(int segPt, int qLeftPt, int qRightPt) {
    if (qLeftPt > qRightPt)
        swap(qLeftPt, qRightPt);

    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        return segTree[segPt].sum;
    }
    pushDown(segPt);
    int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt) 
        ans = (ans + querySum(LEFT_SON, qLeftPt, qRightPt)) % mod;
    if (qRightPt > midPt)
        ans = (ans + querySum(RIGHT_SON, qLeftPt, qRightPt)) % mod;
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
        if (siz[nextPt] > siz[hson[cntPt]])
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

int queryChain(int fstPt, int sndPt) {
    int ans = 0;
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        ans += querySum(1, id[top[fstPt]], id[fstPt]);
        ans %= mod;
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    ans += querySum(1, id[fstPt], id[sndPt]);
    ans %= mod;
    return ans;
}

void updateChain(int fstPt, int sndPt, int val) {
    val %= mod;
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        rangeAdd(1, id[top[fstPt]], id[fstPt], val);
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    rangeAdd(1, id[fstPt], id[sndPt], val);
}

int querySubtree(int rootPt) {
    return querySum(1, id[rootPt], id[rootPt] + siz[rootPt] - 1) % mod;
}

void updateSubtree(int rootPt, int val) {
    val %= mod;
    rangeAdd(1, id[rootPt], id[rootPt] + siz[rootPt] - 1, val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0, cntId = 0;

    int qNum, rootPt;
    cin >> vertexNum >> qNum >> rootPt >> mod;
    rootPt--;
    for (int i = 0; i < vertexNum; i++)
        cin >> arr[i];
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    memset(depth, -1, sizeof(depth));
    memset(hson, -1, sizeof(hson));
    father[rootPt] = -1;
    depth[rootPt] = 0;
    dfs1(rootPt);
    dfs2(rootPt, rootPt);
    build(1, 1, vertexNum);
    
    while (qNum--) {
        int opr, from;
        cin >> opr >> from;
        from--;
        if (opr == 1) {
            int to, val;
            cin >> to >> val;
            to--;
            updateChain(from, to, val);
        } else if (opr == 2) {
            int to;
            cin >> to;
            to--;
            cout << queryChain(from, to) << endl;
        } else if (opr == 3) {
            int val;
            cin >> val;
            updateSubtree(from, val);
        } else {
            cout << querySubtree(from) << endl;
        }
    }

    return 0;
}