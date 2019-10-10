#include <bits/stdc++.h>
using namespace std;
 
#define VERTEX_SIZE 100010
#define EDGE_SIZE 600010
 
class Edge {
public:
    int to, next;
};
 
Edge edges[EDGE_SIZE];
int head[VERTEX_SIZE], ans[VERTEX_SIZE], edgesPt;
bool vis[VERTEX_SIZE];
 
void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int vertexNum, edgeNum; cin >> vertexNum >> edgeNum;
    fill(head + 0, head + vertexNum, -1); edgesPt = 0;
    fill(ans + 0, ans + vertexNum, -1);
    for (int i = 0; i < edgeNum; i++) {
        int from, to; cin >> from >> to; from--; to--;
        addEdge(from, to); addEdge(to, from);
    }
 
    const auto work = [vertexNum, edgeNum](int pt, int which) {
        if (head[pt] == -1)
            return false;
        fill(vis + 0, vis + vertexNum, false); int deg = 0;
        for (int i = head[pt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            vis[nextPt] = true; deg++;
        }
        for (int t = 0; t < vertexNum; t++) {
            if (!vis[t]) {
                ans[t] = which; int cntDeg = 0;
                for (int i = head[t]; i != -1; i = edges[i].next) {
                    int nextPt = edges[i].to;
                    if (!vis[nextPt])
                        return false;
                    cntDeg++;
                }
                if (cntDeg != deg)
                    return false;
            }
        }
        return true;
    };
 
    // First set
    if (!work(0, 1)) {
        cout << -1 << '\n';
        return 0;
    }
    
    int pt = edges[head[0]].to;
    if (!work(pt, 2)) {
        cout << -1 << '\n';
        return 0;
    }
 
    pt = -1;
    for (int i = 0; i < vertexNum && pt == -1; i++)
        if (ans[i] == -1)
            pt = i;
    if (pt == -1) {
        cout << -1 << '\n';
        return 0;
    }
    if (!work(pt, 3)) {
        cout << -1 << '\n';
        return 0;
    }
 
    for (int i = 0; i < vertexNum; i++) {
        if (ans[i] == -1) {
            cout << -1 << '\n';
            return 0;
        }
    }
 
    for (int i = 0; i < vertexNum; i++)
        cout << ans[i] << ' ';
    return 0;
}