#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], vertexNum, edgePt;

int siz[SIZE], father[SIZE], depth[SIZE], hson[SIZE];
int top[SIZE], id[SIZE], orig[SIZE], color[SIZE], cntId;

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegData {
    int num, leftColor, rightColor;
} SegData; 

typedef struct _SegNode {
    int leftPt, rightPt;
    SegData data;
    int lazy;
} SegNode;
SegNode segTree[SIZE << 2];

SegData merge(SegData fst, SegData snd) {
    if (fst.num == 0)
        return snd;
    if (snd.num == 0)
        return fst;

    fst.num += snd.num;
    if (fst.rightColor == snd.leftColor)
        fst.num--;
    fst.rightColor = snd.rightColor;
    return fst;
}

void pushUp(int segPt) {
    segTree[segPt].data = merge(segTree[LEFT_SON].data, segTree[RIGHT_SON].data);
}

void pushDown(int segPt) {
    if (segTree[segPt].lazy != 0) {
        segTree[LEFT_SON].data = {1, segTree[segPt].lazy, segTree[segPt].lazy};
        segTree[RIGHT_SON].data = {1, segTree[segPt].lazy, segTree[segPt].lazy};

        segTree[LEFT_SON].lazy = segTree[segPt].lazy;
        segTree[RIGHT_SON].lazy = segTree[segPt].lazy;

        segTree[segPt].lazy = 0;
    }
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    segTree[segPt].lazy = 0;
    if (leftPt == rightPt) {
        segTree[segPt].data = {1, color[orig[leftPt]], color[orig[leftPt]]};
        return;
    }
    segTree[segPt].data = {0, 0, 0};
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void updateRange(int segPt, int qLeftPt, int qRightPt, int val) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        segTree[segPt].data = {1, val, val};
        segTree[segPt].lazy = val;
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        updateRange(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        updateRange(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

SegData queryRange(int segPt, int qLeftPt, int qRightPt) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        return segTree[segPt].data;
    }
    pushDown(segPt);

    SegData ans = {0, 0, 0};
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = merge(queryRange(LEFT_SON, qLeftPt, qRightPt), ans);
    if (qRightPt > midPt)
        ans = merge(ans, queryRange(RIGHT_SON, qLeftPt, qRightPt));
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

void updateRoute(int fstPt, int sndPt, int val) {
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        updateRange(1, id[top[fstPt]], id[fstPt], val);
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    updateRange(1, id[fstPt], id[sndPt], val);
}

int queryRoute(int fstPt, int sndPt) {
    SegData fstAns = {0, 0, 0}, sndAns = {0, 0, 0};
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]]) {
            sndAns = merge(queryRange(1, id[top[sndPt]], id[sndPt]), sndAns);
            sndPt = father[top[sndPt]];
        } else {
            fstAns = merge(queryRange(1, id[top[fstPt]], id[fstPt]), fstAns);
            fstPt = father[top[fstPt]];
        }
    }

    if (id[fstPt] > id[sndPt]) {
        swap(sndAns.leftColor, sndAns.rightColor);
        return merge(sndAns, merge(queryRange(1, id[sndPt], id[fstPt]), fstAns)).num;
    } else {
        swap(fstAns.leftColor, fstAns.rightColor);
        return merge(fstAns, merge(queryRange(1, id[fstPt], id[sndPt]), sndAns)).num;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0, cntId = 0;
    int qNum;
    cin >> vertexNum >> qNum;
    for (int i = 0; i < vertexNum; i++)
        cin >> color[i];
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    memset(depth, -1, sizeof(depth));
    memset(hson, -1, sizeof(hson));
    depth[0] = 0, father[0] = 0;
    dfs1(0);
    dfs2(0, 0);
    build(1, 1, vertexNum);

    while (qNum--) {
        string opr;
        int from, to;
        cin >> opr >> from >> to;
        from--, to--;
        if (opr[0] == 'C') {
            // Color
            int val;
            cin >> val;
            updateRoute(from, to, val);
        } else {
            // Query
            cout << queryRoute(from, to) << endl;
        }
    }

    return 0;
}
