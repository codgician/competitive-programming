#include <bits/stdc++.h>
using namespace std;

#define SIZE 30010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt, vertexNum;

int father[SIZE], depth[SIZE], siz[SIZE], arr[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt;
    int maxVal;
    long long int sum;
} SegNode;
SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    segTree[segPt].maxVal = max(segTree[LEFT_SON].maxVal, segTree[RIGHT_SON].maxVal);
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt) {
        segTree[segPt].maxVal = arr[orig[leftPt]];
        segTree[segPt].sum = arr[orig[leftPt]];
        return;
    }

    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void update(int segPt, int cntPt, int val) {
    if (segTree[segPt].leftPt == segTree[segPt].rightPt) {
        segTree[segPt].maxVal = val;
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

long long int querySum(int segPt, int qLeftPt, int qRightPt) {
    if (qLeftPt > qRightPt)
        swap(qLeftPt, qRightPt);
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
        return segTree[segPt].sum;

    long long int ans = 0;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans += querySum(LEFT_SON, qLeftPt, qRightPt);
    if (qRightPt > midPt)
        ans += querySum(RIGHT_SON, qLeftPt, qRightPt);
    return ans;
}

int queryMax(int segPt, int qLeftPt, int qRightPt) {
    if (qLeftPt > qRightPt)
        swap(qLeftPt, qRightPt);
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
        return segTree[segPt].maxVal;

    int ans = INT_MIN;
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = max(ans, queryMax(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = max(ans, queryMax(RIGHT_SON, qLeftPt, qRightPt));
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

long long int queryChainSum(int fstPt, int sndPt) {
    long long int ans = 0;
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

int queryChainMax(int fstPt, int sndPt) {
    int ans = INT_MIN;
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        ans = max(ans, queryMax(1, id[top[fstPt]], id[fstPt]));
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    ans = max(ans, queryMax(1, id[fstPt], id[sndPt]));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0, cntId = 0;

    cin >> vertexNum;
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        addEdge(from, to);
        addEdge(to, from);
    }
    for (int i = 0; i < vertexNum; i++)
        cin >> arr[i];
    memset(depth, -1, sizeof(depth));
    memset(hson, -1, sizeof(hson));
    father[0] = -1;
    depth[0] = 0;
    dfs1(0);
    dfs2(0, 0);
    build(1, 1, vertexNum);

    int qNum;
    cin >> qNum;
    while (qNum--) {
        string opr;
        int from, to;
        cin >> opr >> from >> to;
        if (opr[0] == 'C') {
            // CHANGE
            update(1, id[from - 1], to);
        } else if (opr[1] == 'M') {
            // QMAX
            cout << queryChainMax(from - 1, to - 1) << endl;
        } else {
            // QSUM
            cout << queryChainSum(from - 1, to - 1) << endl;
        }
    }
    return 0;
}