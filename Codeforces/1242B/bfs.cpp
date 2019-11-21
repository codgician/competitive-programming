#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE], edgesPt;
list<int> lst; bool vis[SIZE], tag[SIZE];

void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum; cin >> vertexNum >> edgeNum;
    fill(head + 0, head + vertexNum, -1); edgesPt = 0;
    for (int i = 0; i < edgeNum; i++) {
        int from, to; cin >> from >> to; from--; to--;
        addEdge(from, to); addEdge(to, from);
    }
    
    int ans = 0;
    for (int i = 0; i < vertexNum; i++)
        lst.push_back(i), vis[i] = false, tag[i] = false;
    while (!lst.empty()) {
        int cntPt = lst.front(); lst.pop_front();
        queue<int> q; q.push(cntPt);
        while (!q.empty()) {
            int cntPt = q.front(); q.pop();
            vis[cntPt] = true;
            for (int i = head[cntPt]; i != -1; i = edges[i].next)
                tag[edges[i].to] = true;
            auto it = lst.begin();
            while (it != lst.end()) {
                int pt = *it;
                if (!tag[pt]) {
                    q.push(pt); lst.erase(it++);
                    continue;
                }
                ++it;
            }
            for (int i = head[cntPt]; i != -1; i = edges[i].next) 
                tag[edges[i].to] = false;
        }
        ans++;
    }

    cout << ans - 1 << '\n';
    return 0;
}
