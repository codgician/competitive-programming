#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
    int len;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE << 1], edgePt; 
int vertexNum, qNum;

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

typedef struct _Query {
    int id, from, to;
    int lim;
} Query;

Query qArr[SIZE];

/* Segment Tree */

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt;
    int sum;
} SegNode;
SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt) {
        segTree[segPt].sum = 0;
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void update(int segPt, int cntPt, int val) {
    if (segTree[segPt].leftPt == segTree[segPt].rightPt) {
        segTree[segPt].sum = val;
        return;
    }

    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (cntPt <= midPt)
        update(LEFT_SON, cntPt, val);
    else
        update(RIGHT_SON, cntPt, val);
    pushUp(segPt);
}

int querySum(int segPt, int qLeftPt, int qRightPt) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        return segTree[segPt].sum;
    }

    int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += querySum(RIGHT_SON, qLeftPt, qRightPt);
    return ans;
}

/* Tree Chain Partition */

int father[SIZE], depth[SIZE], siz[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;
int val[SIZE], ans[SIZE];

int dsc[SIZE << 1];
pair<int, int> order[SIZE];

void dfs1(int cntPt) {
    siz[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (depth[nextPt] != -1)
            continue;
        father[nextPt] = cntPt;
        depth[nextPt] = depth[cntPt] + 1;
        val[nextPt] = edge[i].len;
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

    if (id[fstPt] + 1 <= id[sndPt] )
        ans += querySum(1, id[fstPt] + 1, id[sndPt]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    memset(depth, -1, sizeof(depth));
    memset(hson, -1, sizeof(hson));
    edgePt = 0, cntId = 0;

    dsc[0] = -1;
    int dscPt = 1;
    cin >> vertexNum >> qNum;
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        int len;
        cin >> from >> to >> len;
        from--, to--;
        addEdge(from, to, len);
        addEdge(to, from, len);
        dsc[dscPt++] = len;
    }

    father[0] = 0, depth[0] = 0, val[0] = -1;
    dfs1(0); dfs2(0, 0);

    for (int i = 0; i < qNum; i++) {
        qArr[i].id = i;
        cin >> qArr[i].from >> qArr[i].to >> qArr[i].lim;
        qArr[i].from--, qArr[i].to--;
        dsc[dscPt++] = qArr[i].lim;
    }

    sort(dsc + 0, dsc + dscPt);
    dscPt = unique(dsc + 0, dsc + dscPt) - dsc;

    for (int i = 0; i < vertexNum; i++) {
        val[i] = lower_bound(dsc + 0, dsc + dscPt, val[i]) - dsc + 1;
        order[i] = make_pair(val[i], i);
    }
    for (int i = 0; i < qNum; i++)
        qArr[i].lim = lower_bound(dsc + 0, dsc + dscPt, qArr[i].lim) - dsc + 1;

    sort(order + 0, order + vertexNum);
    sort(qArr + 0, qArr + qNum, [](const Query & fst, const Query & snd) {
        return fst.lim < snd.lim;
    });

    build(1, 1, vertexNum);

    int cntPt = 0;
    for (int i = 0; i < qNum; i++) {
        while (cntPt < vertexNum && order[cntPt].first <= qArr[i].lim) {
            // Add into segment tree
            update(1, id[order[cntPt].second], 1);
            cntPt++;
        }

        // Query answer
        ans[qArr[i].id] = queryRoute(qArr[i].from, qArr[i].to);
    }

    for (int i = 0; i < qNum; i++)
        cout << ans[i] << '\n';

    return 0;
}
