#include <bits/stdc++.h>
using namespace std;

#define SIZE 50010

class State {
public:
    int from, to, rank;
    long long int len;
    bool operator < (const State & snd) const {
        return len > snd.len;
    }
};

vector<pair<int, int> > edges[SIZE];
int ques[SIZE], vertexNum, edgeNum;
long long int ans[SIZE];

void addEdge(int from, int to, int len) {
    edges[from].push_back(make_pair(len, to));
}

void bfs(int lim) {
    priority_queue<State> pq;
    for (int i = 0; i < vertexNum; i++) {
        sort(edges[i].begin(), edges[i].end());
        if (edges[i].size())
            pq.push(State{i, edges[i].front().second, 0, edges[i].front().first});
    }

    for (int t = 0; t <= lim; t++) {
        auto top = pq.top(); pq.pop();
        ans[t] = top.len;

        if ((int)edges[top.from].size() > top.rank + 1) {
            State nxtst = top; nxtst.to = edges[top.from][top.rank + 1].second;
            nxtst.len += edges[top.from][top.rank + 1].first - edges[top.from][top.rank].first;
            nxtst.rank++; pq.push(nxtst); 
        }

        if (edges[top.to].size()) {
            State nxtst = State{top.to, edges[top.to].front().second, 0, top.len + edges[top.to].front().first};
            pq.push(nxtst);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int qNum; cin >> vertexNum >> edgeNum >> qNum;
        for (int i = 0; i < vertexNum; i++)
            edges[i].clear();
        for (int i = 0; i < edgeNum; i++) {
            int from, to, len; cin >> from >> to >> len;
            from--; to--; addEdge(from, to, len);
        }

        int lim = 0;
        for (int i = 0; i < qNum; i++) {
            cin >> ques[i]; ques[i]--;
            lim = max(lim, ques[i]);
        }

        bfs(lim);

        for (int i = 0; i < qNum; i++)
            cout << ans[ques[i]] << '\n';
    }

    return 0;
}