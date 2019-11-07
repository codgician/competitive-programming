#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 8010
 
class Edge {
public:
	int to, next, len;
};
 
Edge edges[SIZE << 1];
int head[SIZE], edgesPt;
 
void addEdge(int from, int to, int len) {
	edges[edgesPt] = {to, head[from], len};
	head[from] = edgesPt++;
}
 
map<pair<int, int>, int> mp;
 
int vertexNum;
int id(const pair<int, int> & p) { 
	if (mp.find(p) == mp.end())
		mp[p] = vertexNum++;
	return mp[p];
}
 
int dist[SIZE], ans, banPt; bool vis[SIZE];
 
void dijkstra(int startPt) {
    for (int i = 0; i < vertexNum; i++)
        vis[i] = false, dist[i] = INT_MAX;
    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(0, startPt));
    dist[startPt] = 0;
    while (!pq.empty()) {
        int cntPt = pq.top().second; pq.pop();
        if (vis[cntPt])
            continue;
        vis[cntPt] = true;
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            if (i == banPt || i == (banPt ^ 1))
                continue;
            int nextPt = edges[i].to;
            if (dist[nextPt] > dist[cntPt] + edges[i].len) {
                dist[nextPt] = dist[cntPt] + edges[i].len;
                pq.push(make_pair(-dist[nextPt], nextPt));
            }
        }
    }
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int caseNum; cin >> caseNum;
	for (int t = 1; t <= caseNum; t++) {
		memset(head, -1, sizeof(head));
		edgesPt = 0; vertexNum = 0; mp.clear();
		int edgeNum; cin >> edgeNum;
		while (edgeNum--) {
			pair<int, int> from, to; int len;
			cin >> from.first >> from.second >> to.first >> to.second >> len;
			int fstPt = id(from), sndPt = id(to);
			addEdge(fstPt, sndPt, len); addEdge(sndPt, fstPt, len);
		}
		
		ans = INT_MAX;
		for (int i = 0; i < edgesPt; i += 2) {
			int from = edges[i ^ 1].to, to = edges[i].to; banPt = i;
            if (edges[i].len >= ans)
                continue;
            dijkstra(from);
			if (dist[to] != INT_MAX)
				ans = min(ans, dist[to] + edges[i].len);
		}
		cout << "Case #" << t << ": " << (ans == INT_MAX ? 0 : ans) << '\n';
	}
	
	return 0;
}