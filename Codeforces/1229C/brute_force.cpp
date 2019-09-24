#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

vector<int> graph[SIZE];
int inDeg[SIZE], outDeg[SIZE];

void addEdge(int from, int to) {
    graph[to].push_back(from);
    inDeg[to]++; outDeg[from]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum; cin >> vertexNum >> edgeNum;
    fill(inDeg + 0, inDeg + vertexNum, 0);
    fill(outDeg + 0, outDeg + vertexNum, 0);
    for (int i = 0; i < edgeNum; i++) {
        int from, to; cin >> from >> to;
        if (from < to)
            swap(from, to);
        from--; to--; addEdge(from, to);
    }

    long long int ans = 0;
    for (int i = 0; i < vertexNum; i++)
        ans += 1ll * inDeg[i] * outDeg[i];
    cout << ans << '\n';
    int qNum; cin >> qNum;
    while (qNum--) {
        int to; cin >> to; to--;
        assert(graph[to].size() == inDeg[to]);
        ans -= 1ll * inDeg[to] * outDeg[to];
        outDeg[to] += 1ll * inDeg[to]; inDeg[to] = 0;
        for (const auto & from : graph[to]) {
            ans -= 1ll * inDeg[from] * outDeg[from];
            graph[from].push_back(to); 
            inDeg[from]++; outDeg[from]--;
            ans += 1ll * inDeg[from] * outDeg[from];
        }
        graph[to].clear();
        cout << ans << '\n';
    }

    return 0;
}