#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE], deg[SIZE], edgesPt;
int mark[SIZE], eid[SIZE], ret[SIZE << 1];
pair<int, int> e[SIZE << 1];

void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum; 
    while (cin >> vertexNum >> edgeNum) {
        fill(head + 0, head + vertexNum, -1); edgesPt = 0;
        fill(deg + 0, deg + vertexNum, 0);
        fill(mark + 0, mark + vertexNum, -1);
        for (int i = 0; i < edgeNum; i++) {
            cin >> e[i].first >> e[i].second; 
            e[i].first--; e[i].second--; ret[i] = 0;
            deg[e[i].first]++; deg[e[i].second]++;
        }

        for (int i = 0; i < edgeNum; i++) {
            int from = e[i].first, to = e[i].second;
            if (deg[from] > deg[to] || (deg[from] == deg[to] && from > to))
                swap(from, to);
            addEdge(from, to);
        }

        long long int ans = 0;
        for (int i = 0; i < edgeNum; i++) {
            int fstPt = e[i].first, sndPt = e[i].second;
            for (int j = head[fstPt]; j != -1; j = edges[j].next) {
                int nextPt = edges[j].to;
                mark[nextPt] = i; eid[nextPt] = j;
            }
            for (int j = head[sndPt]; j != -1; j = edges[j].next) {
                int thdPt = edges[j].to;
                if (mark[thdPt] == i) {
                    ret[i]++; ret[j]++; ret[eid[thdPt]]++;
                }
            }
        }

        const auto comb2 = [](long long int n) { return (n * (n - 1)) >> 1; }; 
        for (int i = 0; i < edgeNum; i++)
            ans += comb2(ret[i]);
        cout << ans << '\n';
    }

    return 0;
}