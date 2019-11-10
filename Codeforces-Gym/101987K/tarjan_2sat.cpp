#include <bits/stdc++.h>
using namespace std;

#define SIZE 20010

class Edge {
public:
    int to, next;
};

Edge edges[2][SIZE << 2];
int head[2][SIZE], edgesPt[2], vertexNum;
int quit[SIZE], sccId[SIZE], cntTime; bool vis[SIZE];

void addEdge(int id, int from, int to) {
    edges[id][edgesPt[id]] = {to, head[id][from]};
    head[id][from] = edgesPt[id]++;
}

void dfs1(int cntPt) {
    vis[cntPt] = true;
    for (int i = head[0][cntPt]; i != -1; i = edges[0][i].next) {
        int nextPt = edges[0][i].to;
        if (!vis[nextPt])
            dfs1(nextPt);
    }
    quit[cntTime++] = cntPt;
}

void dfs2(int cntPt, int sccPt) {
    vis[cntPt] = true; sccId[cntPt] = sccPt;
    for (int i = head[1][cntPt]; i != -1; i = edges[1][i].next) {
        int nextPt = edges[1][i].to;
        if (!vis[nextPt])
            dfs2(nextPt, sccPt);
    }
}

bool twoSat() {
    fill(vis + 0, vis + vertexNum, false);
    for (int i = 0; i < vertexNum; i++)
        if (!vis[i])
            dfs1(i);
    fill(vis + 0, vis + vertexNum, false);
    int sccPt = 0;
    for (int i = cntTime - 1; i >= 0; i--)
        if (!vis[quit[i]])
            dfs2(quit[i], sccPt++);
    for (int i = 0; i < vertexNum; i += 2)
        if (sccId[i] == sccId[i ^ 1]) 
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int lightNum, guestNum; cin >> lightNum >> guestNum;
    for (int i = 0; i < 2; i++)
        fill(head[i] + 0, head[i] + (lightNum << 1), -1), edgesPt[i] = 0;
    cntTime = 0; vertexNum = lightNum << 1;
    for (int i = 0; i < guestNum; i++) {
        vector<pair<int, bool> > v;
        for (int j = 0; j < 3; j++) {
            int id; char ch; cin >> id >> ch;
            v.push_back(make_pair(id - 1, ch == 'R'));  // 0: B, 1: R
        }
        for (int j = 0; j < 3; j++) {
            const auto & a = v[j], & b = v[(j + 1) % 3], & c = v[(j + 2) % 3]; 
            const auto add = [](int from, int to) {
                addEdge(0, from, to); addEdge(1, to, from);
            };
            add(a.first << 1 | (a.second ^ 1), b.first << 1 | b.second);
            add(a.first << 1 | (a.second ^ 1), c.first << 1 | c.second);
        }
    }
    
    if (!twoSat()) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < lightNum; i++)
        cout << (sccId[i << 1] > sccId[i << 1 | 1] ? 'B' : 'R');
    cout << '\n';
    return 0;
}