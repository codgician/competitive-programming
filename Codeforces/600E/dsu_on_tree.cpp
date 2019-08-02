#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE], edgesPt;
int color[SIZE], siz[SIZE], hson[SIZE];
int mp[SIZE], cntHson, maxv;
long long int ans[SIZE], maxSum;

void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}

void dfs1(int cntPt, int fatherPt) {
    siz[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs1(nextPt, cntPt);
        siz[cntPt] += siz[nextPt];
        if (hson[cntPt] == -1 || siz[nextPt] > siz[hson[cntPt]])
            hson[cntPt] = nextPt;
    }
}

void calc(int cntPt, int fatherPt, int val) {
    mp[color[cntPt]] += val;
    if (val > 0) {
        if (mp[color[cntPt]] > maxv)
            maxv = mp[color[cntPt]], maxSum = color[cntPt];
        else if (mp[color[cntPt]] == maxv)
            maxSum += color[cntPt];
    }

    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt || nextPt == cntHson)
            continue;
        calc(nextPt, cntPt, val);
    }
}

void dfs2(int cntPt, int fatherPt, bool keep) {
    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt || nextPt == hson[cntPt])
            continue;
        dfs2(nextPt, cntPt, false);
    }

    if (hson[cntPt] != -1)
        dfs2(hson[cntPt], cntPt, true), cntHson = hson[cntPt];
    calc(cntPt, fatherPt, 1); cntHson = -1;
    ans[cntPt] = maxSum;
    if (!keep)
        calc(cntPt, fatherPt, -1), maxv = 0, maxSum = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum; cin >> vertexNum;
    fill(head + 0, head + vertexNum, -1);
    fill(hson + 0, hson + vertexNum, -1);
    fill(mp + 0, mp + vertexNum, 0);
    edgesPt = 0;
    for (int i = 0; i < vertexNum; i++)
        cin >> color[i];
    for (int i = 1; i < vertexNum; i++) {
        int from, to; cin >> from >> to;
        from--; to--;
        addEdge(from, to); addEdge(to, from);
    }

    dfs1(0, -1);
    dfs2(0, -1, false);
    for (int i = 0; i < vertexNum; i++)
        cout << ans[i] << ' ';
    cout << '\n';

    return 0;
}
