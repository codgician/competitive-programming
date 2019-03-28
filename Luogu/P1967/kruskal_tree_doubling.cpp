#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define EDGE_SIZE 500010

typedef struct _Data {
    int from, to, lim;
} Data;

Data arr[EDGE_SIZE];

typedef struct _Edge {
    int to, next;
    int lim;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], vertexNum, edgePt;
int depth[SIZE], anc[SIZE][20], minLim[SIZE][20];
int maxDepth;

int parent[SIZE];

int getParent(int n) {
    if (parent[n] == n) {
        return n;
    } else {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt);
    sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    parent[sndPt] = fstPt;
    return true;
}

void addEdge(int from, int to, int lim) {
    edge[edgePt] = {to, head[from], lim};
    head[from] = edgePt++;
}

void dfs(int cntPt) {
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (depth[nextPt] != -1)
            continue;
        depth[nextPt] = depth[cntPt] + 1;
        anc[nextPt][0] = cntPt;
        minLim[nextPt][0] = edge[i].lim;
        dfs(nextPt);
    }
}

void st() {
    for (int j = 1; j <= maxDepth; j++) {
        for (int i = 0; i < vertexNum; i++) {
            if (anc[i][j - 1] == -1)
                continue;
            minLim[i][j] = min(minLim[i][j - 1], minLim[anc[i][j - 1]][j - 1]);
            anc[i][j] = anc[anc[i][j - 1]][j - 1];
        }
    }
}

int queryMaxLim(int fstPt, int sndPt) {
    int ans = INT_MAX;
    if (depth[fstPt] < depth[sndPt])
        swap(fstPt, sndPt);
    for (int i = maxDepth; i >= 0; i--) {
        if (anc[fstPt][i] != -1 && depth[anc[fstPt][i]] >= depth[sndPt]) {
            ans = min(ans, minLim[fstPt][i]);
            fstPt = anc[fstPt][i];
        }
    }
    if (fstPt == sndPt)
        return ans;
    for (int i = maxDepth; i >= 0; i--) {
        if (anc[fstPt][i] != -1 && anc[sndPt][i] != -1 && anc[fstPt][i] != anc[sndPt][i]) {
            ans = min(ans, min(minLim[fstPt][i], minLim[sndPt][i]));
            fstPt = anc[fstPt][i], sndPt = anc[sndPt][i];
        }
    }
    return min(ans, min(minLim[fstPt][0], minLim[sndPt][0]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    edgePt = 0;
    int edgeNum;
    cin >> vertexNum >> edgeNum;
    maxDepth = log2(vertexNum) + 1;
    for (int i = 0; i < edgeNum; i++) {
        cin >> arr[i].from >> arr[i].to >> arr[i].lim;
        arr[i].from--, arr[i].to--;
    }

    sort(arr + 0, arr + edgeNum, [](Data & fst, Data & snd) {
        return fst.lim > snd.lim;
    });

    for (int i = 0; i < vertexNum; i++)
        parent[i] = i;
    for (int i = 0; i < edgeNum; i++) {
        if (merge(arr[i].from, arr[i].to)) {
            addEdge(arr[i].from, arr[i].to, arr[i].lim);
            addEdge(arr[i].to, arr[i].from, arr[i].lim);
        }
    }

    for (int i = 1; i < vertexNum; i++) {
        if (merge(0, i)) {
            addEdge(0, i, -1);
            addEdge(i, 0, -1);
        }
    }

    memset(depth, -1, sizeof(depth));
    memset(anc, -1, sizeof(anc));
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j <= maxDepth; j++)
            minLim[i][j] = INT_MAX;
    depth[0] = 0; 
    dfs(0);
    st();

    int qNum;
    cin >> qNum;
    while (qNum--) {
        int from, to;
        cin >> from >> to;
        from--, to--;
        cout << queryMaxLim(from, to) << endl;
    }

    return 0;
}