#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

const long long int mod = 1e9 + 7;

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE], edgesPt;
int lg[SIZE];

long long int vals[SIZE], ggcd[SIZE][20], ans;

void addEdge(int from, int to) {
    edges[edgesPt] = Edge{to, head[from]};
    head[from] = edgesPt++;
}

int depth[SIZE], anc[SIZE][20];
int vertexNum, maxDepth;

void bfs(int startPt) {
    fill(depth + 0, depth + vertexNum, -1);
    for (int i = 0; i < vertexNum; i++)
        fill(anc[i] + 0, anc[i] + maxDepth, -1);
    queue<int> q; q.push(startPt);
    depth[startPt] = 0;

    while (!q.empty()) {
        int cntPt = q.front(); q.pop();
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            if (depth[nextPt] != -1)
                continue;
            depth[nextPt] = depth[cntPt] + 1;
            anc[nextPt][0] = cntPt;
            ggcd[nextPt][0] = __gcd(vals[cntPt], vals[nextPt]);
            for (int j = 1; j < maxDepth; j++) {
                if (anc[nextPt][j - 1] != -1) {
                    anc[nextPt][j] = anc[anc[nextPt][j - 1]][j - 1];
                    ggcd[nextPt][j] = __gcd(ggcd[nextPt][j - 1], ggcd[anc[nextPt][j - 1]][j - 1]);
                }
            }
            q.push(nextPt);
        }
    }
}

void solve(int cntPt) {
    long long int v = 0; 
    while (cntPt != -1) {
        v = __gcd(v, vals[cntPt]);
        const auto getNext = [cntPt, v]() {
            int retPt = cntPt; 
            for (int i = lg[depth[cntPt] + 1]; i >= 0 && retPt != 0; i--) {
                const auto check = [retPt, i, v]() {
                    return ggcd[retPt][i] == 0 || (v != 0 && ggcd[retPt][i] % v == 0);
                };
                if (anc[retPt][i] != -1 && check()) {
                    retPt = anc[retPt][i];
                    i = lg[depth[retPt] + 1] + 1;
                }
            }
            return retPt;
        };
        int nextPt = getNext();
        ans = (ans + (depth[cntPt] - depth[nextPt] + 1) * v % mod) % mod;
        cntPt = anc[nextPt][0]; 
    }
}

void initLg() {
    int low = 1, upp = 2, v = 0;
    while (low < SIZE) {
        fill(lg + low, lg + min(SIZE, upp), v);
        v++; low = upp; upp <<= 1;
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initLg(); cin >> vertexNum;
    fill(head + 0, head + vertexNum, -1); edgesPt = 0;
    maxDepth = lg[vertexNum] + 1;
    for (int i = 0; i < vertexNum; i++)
        cin >> vals[i];
    for (int i = 1; i < vertexNum; i++) {
        int from, to; cin >> from >> to; from--; to--;
        addEdge(from, to); addEdge(to, from);
    }

    bfs(0); ans = 0;
    for (int i = 0; i < vertexNum; i++)
        solve(i);
    cout << ans << '\n';
    return 0;
}