#include <bits/stdc++.h>
using namespace std;

#define SIZE 10010

typedef struct _Edge {
    int to, next;
    long long int len;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;

int depth[SIZE], anc[SIZE][20];
long long int dist[SIZE];
int vertexNum, maxDepth;

int parent[SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt) {
        return cntPt;
    } else {
        parent[cntPt] = getParent(parent[cntPt]);
        return parent[cntPt];
    }
}

void merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt != sndPt)
        parent[sndPt] = fstPt;
}

void addEdge(int from, int to, long long int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

void bfs(int startPt) {
    memset(depth, -1, sizeof(depth));
    memset(dist, 0, sizeof(dist));
    memset(anc, -1, sizeof(anc));
    queue<int> q;
    q.push(startPt);
    depth[startPt] = 0;

    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();

        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            if (depth[nextPt] != -1)
                continue;
            depth[nextPt] = depth[cntPt] + 1;
            dist[nextPt] = dist[cntPt] + edge[i].len;
            anc[nextPt][0] = cntPt;
            for (int j = 1; j <= maxDepth; j++) {
                if (anc[nextPt][j - 1] != -1) {
                    anc[nextPt][j] = anc[anc[nextPt][j - 1]][j - 1];
                }
            }
            q.push(nextPt);
        }
    }
}

int getLca(int fstPt, int sndPt) {
    if (depth[fstPt] < depth[sndPt])
        swap(fstPt, sndPt);
    for (int i = maxDepth; i >= 0; i--)
        if (anc[fstPt][i] != -1 && depth[anc[fstPt][i]] >= depth[sndPt])
            fstPt = anc[fstPt][i];
    if (fstPt == sndPt)
        return fstPt;
    for (int i = maxDepth; i >= 0; i--)
        if (anc[fstPt][i] != -1 && anc[sndPt][i] != -1 && anc[fstPt][i] != anc[sndPt][i])
            fstPt = anc[fstPt][i], sndPt = anc[sndPt][i];
    return anc[fstPt][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int edgeNum, qNum;
    while (cin >> vertexNum >> edgeNum >> qNum) {
        for (int i = 0; i <= vertexNum; i++)
            parent[i] = i, head[i] = -1;
        edgePt = 0;
        for (int i = 0; i < edgeNum; i++) {
            int from, to, len;
            cin >> from >> to >> len;
            from--, to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
            merge(from, to);
        }

        for (int i = 0; i < vertexNum; i++) {
            if (getParent(i) != getParent(vertexNum)) {
                addEdge(i, vertexNum, 0);
                addEdge(vertexNum, i, 0);
                merge(i, vertexNum);
            }
        }

        int rootPt = vertexNum++;
        maxDepth = log2(vertexNum);
        bfs(rootPt);

        while (qNum--) {
            int from, to;
            cin >> from >> to;
            from--, to--;

            int lca = getLca(from, to);
            if (lca == rootPt) {
                cout << "Not connected\n";
            } else {
                cout << dist[from] + dist[to] - (dist[lca] << 1) << '\n';
            }
        }
        
    }

    return 0;
}