#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next, id;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt, vertexNum;

int father[SIZE], depth[SIZE], siz[SIZE];
int top[SIZE], hson[SIZE], id[SIZE], orig[SIZE], cntId;

long long int pfx[2][SIZE];

/* Tree Chain Partition */

void addEdge(int from, int to, int id) {
    edge[edgePt] = {to, head[from], id};
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

void updateRoute(int which, int fstPt, int sndPt, long long int val) {
    while (top[fstPt] != top[sndPt]) {
        if (depth[top[fstPt]] < depth[top[sndPt]])
            swap(fstPt, sndPt);
        pfx[which][id[top[fstPt]]] += val;
        pfx[which][id[fstPt] + 1] -= val;
        fstPt = father[top[fstPt]];
    }

    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    if (id[fstPt] + which <= id[sndPt]) {
        pfx[which][id[fstPt] + which] += val;
        pfx[which][id[sndPt] + 1] -= val;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        int qNum;
        cin >> vertexNum >> qNum;
        fill(pfx[0] + 0, pfx[0] + vertexNum + 1, 0);
        fill(pfx[1] + 0, pfx[1] + vertexNum + 1, 0);
        fill(head + 0, head + vertexNum, -1);
        edgePt = 0; cntId = 0;

        for (int i = 1; i < vertexNum; i++) {
            int from, to; cin >> from >> to; from--; to--;
            addEdge(from, to, i - 1); addEdge(to, from, i - 1);
        }

        fill(depth + 0, depth + vertexNum, -1);
        fill(hson + 0, hson + vertexNum, -1);
        father[0] = 0, depth[0] = 0;
        dfs1(0); dfs2(0, 0);

        while (qNum--) {
            string op; int from, to; long long int val;
            cin >> op >> from >> to >> val;
            from--; to--;
            updateRoute(op[3] - '1', from, to, val);
        }

        for (int t = 0; t < 2; t++)
            for (int i = 1; i <= vertexNum + 1; i++)
                pfx[t][i] += pfx[t][i - 1];

        cout << "Case #" << t << ":\n";
        for (int i = 0; i < vertexNum; i++)
            cout << pfx[0][id[i]] << (i == vertexNum - 1 ? '\n' : ' ');
        for (int i = 0; i < edgePt; i += 2)
            cout << pfx[1][id[(depth[edge[i].to] > depth[edge[i ^ 1].to] ? edge[i].to : edge[i ^ 1].to)]] << (i + 2 >= edgePt ? '\n' : ' ');
        if (edgePt == 0)
            cout << '\n';   // otherwise Presentation Error
    }

    return 0;
}