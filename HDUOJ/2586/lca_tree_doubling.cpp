#include <bits/stdc++.h>
using namespace std;

#define SIZE 40010

typedef struct _Edge {
    int to, next;
    int len;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;
int depth[SIZE], dist[SIZE], anc[SIZE][20];
int vertexNum, maxDepth;

void addEdge(int from, int to, int len) {
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
            for (int j = 1; j <= maxDepth; j++)
                if (anc[nextPt][j - 1] != -1)
                    anc[nextPt][j] = anc[anc[nextPt][j - 1]][j - 1];
            q.push(nextPt);
        }
    }
}

int lca(int fstPt, int sndPt) {
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
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(head, -1, sizeof(head));
        edgePt = 0;
        int qNum;
        cin >> vertexNum >> qNum;
        maxDepth = log2(vertexNum) + 1;

        for (int i = 1; i < vertexNum; i++) {
            int from, to, len;
            cin >> from >> to >> len;
            from--, to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }

        bfs(0);

        for (int i = 0; i < qNum; i++) {
            int fstPt, sndPt;
            cin >> fstPt >> sndPt;
            fstPt--, sndPt--;
            int ans = dist[fstPt] + dist[sndPt];
            int lcaPt = lca(fstPt, sndPt);
            if (lcaPt != -1)
                ans -= dist[lcaPt] << 1;
            cout << ans << endl;
        }
    }

    return 0;
}