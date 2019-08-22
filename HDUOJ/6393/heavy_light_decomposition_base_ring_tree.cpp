#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
    int len, pt;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;
int vertexNum, extraPt;

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

/* Disjoint Set */

int parent[SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt) {
        return cntPt;
    } else {
        parent[cntPt] = getParent(parent[cntPt]);
        return parent[cntPt];
    }
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    parent[sndPt] = fstPt;
    return true;
}

/* Heavy-light Decomposition */

int father[SIZE], depth[SIZE], siz[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;
int valArr[SIZE];

void dfs1(int cntPt) {
    siz[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (depth[nextPt] != -1)
            continue;
        father[nextPt] = cntPt;
        depth[nextPt] = depth[cntPt] + 1;
        valArr[nextPt] = edge[i].len;
        edge[i].pt = nextPt;
        edge[i ^ 1].pt = nextPt;
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

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt;
    long long int sum;
} SegNode;
SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    segTree[segPt].sum = segTree[LEFT_SON].sum + segTree[RIGHT_SON].sum;
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;

    if (leftPt == rightPt) {
        segTree[segPt].sum = valArr[orig[leftPt]];
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

long long int querySum(int segPt, int qLeftPt, int qRightPt) {
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

long long int queryRoute(int fstPt, int sndPt) {
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

int getLca(int fstPt, int sndPt) {
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] >= depth[top[sndPt]])
            fstPt = father[top[fstPt]];
        else
            sndPt = father[top[sndPt]];
    }
    return depth[fstPt] < depth[sndPt] ? fstPt : sndPt;
}

long long int queryLen(int fstPt, int sndPt) {
    int lca = getLca(fstPt, sndPt);
    return queryRoute(fstPt, sndPt) - queryRoute(lca, lca);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(head, -1, sizeof(head));
        edgePt = 0, cntId = 0;

        int qNum;
        cin >> vertexNum >> qNum;
        for (int i = 0; i < vertexNum; i++)
            parent[i] = i;
        for (int i = 0; i < vertexNum; i++) {
            int from, to, len;
            cin >> from >> to >> len;
            from--, to--;

            if (merge(from, to)) {
                addEdge(from, to, len);
                addEdge(to, from, len);
            } else {
                extraPt = i;
                edge[edgePt++] = {to, -1, len};
                edge[edgePt++] = {from, -1, len};
            }
        }

        memset(depth, -1, sizeof(depth));
        memset(hson, -1, sizeof(hson));
        father[0] = 0, depth[0] = 0, valArr[0] = 0;
        dfs1(0);
        dfs2(0, 0);
        build(1, 1, vertexNum);

        while (qNum--) {
            int opr, fst, snd;
            cin >> opr >> fst >> snd;
            if (opr == 0) {
                fst--;
                edge[fst << 1].len = snd;
                edge[fst << 1 | 1].len = snd;
                if (fst != extraPt)
                    update(1, id[edge[fst << 1].pt], snd);
            } else {
                fst--, snd--;
                long long int ans1 = queryLen(fst, snd);
                long long int ans2 = edge[extraPt << 1].len + min(queryLen(fst, edge[extraPt << 1].to) + queryLen(edge[extraPt << 1 | 1].to, snd), 
                                                                queryLen(fst, edge[extraPt << 1 | 1].to) + queryLen(edge[extraPt << 1].to, snd));
                
                cout << min(ans1, ans2) << '\n';
            }
        }
    }

    return 0;
}