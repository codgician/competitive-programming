#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
const int mod = 1e9 + 7;

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE], edgesPt;

long long int vals[SIZE], ans;

void addEdge(int from, int to) {
    edges[edgesPt] = Edge{to, head[from]};
    head[from] = edgesPt++;
}

void dfs(int cntPt, int fatherPt, int dep, vector<pair<long long int, int> > v) {
    auto v1 = v; v.clear();
    v1.push_back(make_pair(0, dep));
    for (const auto & p : v1) {
        long long int gcd = __gcd(p.first, vals[cntPt]);
        if (!v.empty() && v.back().first == gcd)
            continue;
        v.push_back(make_pair(gcd, p.second));
    }

    int siz = v.size(), last = dep + 1;
    for (int i = siz - 1; i >= 0; i--) {
        auto & p = v[i];
        ans = (ans + (last - p.second) * p.first) % mod;
        last = p.second;
    }

    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt, dep + 1, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum; cin >> vertexNum;
    fill(head + 0, head + vertexNum, -1); edgesPt = 0;
    for (int i = 0; i < vertexNum; i++)
        cin >> vals[i];
    for (int i = 1; i < vertexNum; i++) {
        int from, to; cin >> from >> to; from--; to--;
        addEdge(from, to); addEdge(to, from);
    }

    ans = 0;
    dfs(0, -1, 0, {});
    cout << ans << '\n';

    return 0;
}