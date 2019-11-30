#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

class Edge {
public:
    int to, next;
};
Edge edges[SIZE << 1];
int head[SIZE], edgesPt;
int conn[SIZE], siz[SIZE], dp[SIZE];
pair<int, int> rng[SIZE];

class Subt {
public:
    int edgeNum, leftPt, rightPt;
    bool operator < (const Subt & snd) const {
        return rightPt < snd.rightPt;
    }
};
vector<Subt> vec;

void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}

void dfs(int cntPt, int fatherPt) {
    siz[cntPt] = 1; rng[cntPt] = make_pair(INT_MAX, INT_MIN);
    if (conn[cntPt] != -1) 
        rng[cntPt] = make_pair(conn[cntPt], conn[cntPt]);

    const auto upd = [](const pair<int, int> & fst, const pair<int, int> & snd) {
        return make_pair(min(fst.first, snd.first), max(fst.second, snd.second));
    };

    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        siz[cntPt] += siz[nextPt];
        rng[cntPt] = upd(rng[cntPt], rng[nextPt]);
    }

    vec.push_back(Subt{siz[cntPt] - (fatherPt == -1), rng[cntPt].first + 1, rng[cntPt].second + 1});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int deviceNum, vertexNum; cin >> deviceNum >> vertexNum;
    fill(head + 0, head + vertexNum, -1);
    fill(conn + 0, conn + vertexNum, -1);
    edgesPt = 0; vec.clear();
    for (int i = 1; i < vertexNum; i++) {
        int to; cin >> to; to--;
        addEdge(i, to); addEdge(to, i);
    }
    for (int i = 0; i < deviceNum; i++) {
        int pt; cin >> pt; pt--;
        conn[pt] = i;
    }

    dfs(0, -1);

    cin >> vertexNum;
    fill(head + 0, head + vertexNum, -1);
    fill(conn + 0, conn + vertexNum, -1);
    edgesPt = 0;
    for (int i = 1; i < vertexNum; i++) {
        int to; cin >> to; to--;
        addEdge(i, to); addEdge(to, i);
    }
    for (int i = 0; i < deviceNum; i++) {
        int pt; cin >> pt; pt--;
        conn[pt] = i;
    }

    dfs(0, -1);

    sort(vec.begin(), vec.end());
    fill(dp + 0, dp + deviceNum + 1, 0);
    for (const auto & s : vec)
        dp[s.rightPt] = max(dp[s.rightPt], dp[s.leftPt - 1] + s.edgeNum);
    cout << dp[deviceNum] << '\n';

    return 0;
}