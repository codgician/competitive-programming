#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], vertexNum, edgePt;

int father[SIZE], depth[SIZE], siz[SIZE], arr[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;

int ord[SIZE], bit[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    for (int i = pos; i <= vertexNum + 1; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
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
        add(id[top[fstPt]], 1);
        add(id[fstPt] + 1, -1);
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);

    add(id[fstPt], 1);
    add(id[sndPt] + 1, -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    memset(bit, 0, sizeof(bit));
    edgePt = 0, cntId = 0;

    cin >> vertexNum;
    for (int i = 0; i < vertexNum; i++) {
        cin >> ord[i];
        ord[i]--;
    }
    for (int i = 1; i < vertexNum; i++) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    int rootPt = ord[0];
    memset(depth, -1, sizeof(depth));
    memset(hson, -1, sizeof(hson));
    depth[rootPt] = 0, father[rootPt] = -1;
    dfs1(rootPt);
    dfs2(rootPt, rootPt);

    for (int i = 1; i < vertexNum; i++) {
        updateRoute(ord[i - 1], ord[i], 1);
        add(id[ord[i]], -1);
        add(id[ord[i]] + 1, 1);
    }

    for (int i = 0; i < vertexNum; i++) {
        cout << prefixSum(id[i]) << endl;
    }
    
    return 0;
}