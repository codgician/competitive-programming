#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 3010
 
class Edge {
public:
    int to, next, len;
};
 
Edge edges[SIZE << 3];
int head[SIZE], edgesPt;
 
void addEdge(int from, int to, int len) {
    edges[edgesPt] = {to, head[from], len};
    head[from] = edgesPt++;
}
 
int dist[SIZE], cnt[SIZE], vertexNum;
bool inQueue[SIZE];
 
bool spfa(int lim) {
    queue<int> q;
    for (int i = 0; i < vertexNum; i++) {
        cnt[i] = 0; dist[i] = 0;
        inQueue[i] = true; q.push(i);
    }
    dist[vertexNum - 1] = lim;
 
    while (!q.empty()) {
        int cntPt = q.front(); q.pop(); inQueue[cntPt] = false;
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            if (dist[nextPt] < dist[cntPt] + edges[i].len) {
                dist[nextPt] = dist[cntPt] + edges[i].len;
                cnt[nextPt] = cnt[cntPt] + 1;
                if (cnt[nextPt] >= vertexNum)
                    return false;
                if (!inQueue[nextPt]) {
                    q.push(nextPt); inQueue[nextPt] = true;
                }
            }
        }
    }
        
    return true;
}
 
class Lims {
public:
    int l, r, k;
};
 
Lims fst[SIZE], snd[SIZE];
int len, fstNum, sndNum;
 
bool check(int lim) {
    fill(head + 0, head + vertexNum, -1); edgesPt = 0;
    for (int i = 1; i < vertexNum; i++)
        addEdge(i - 1, i, 0), addEdge(i, i - 1, -1);
    for (int i = 0; i < fstNum; i++)
        addEdge(fst[i].l - 1, fst[i].r, fst[i].k);
    for (int i = 0; i < sndNum; i++)
        addEdge(snd[i].r, snd[i].l - 1, snd[i].k - lim);
    addEdge(vertexNum - 1, 0, -lim);
 
    auto ret = spfa(lim);
    if (dist[0] != 0 || dist[vertexNum - 1] > lim)
        return false;
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> len >> fstNum >> sndNum;
        vertexNum = len + 1;
        int leftPt = 0, rightPt = len, ans = len;
        for (int i = 0; i < fstNum; i++)
            cin >> fst[i].l >> fst[i].r >> fst[i].k, leftPt = max(leftPt, fst[i].k);
        for (int i = 0; i < sndNum; i++)
            cin >> snd[i].l >> snd[i].r >> snd[i].k, leftPt = max(leftPt, snd[i].k);
 
        while (leftPt <= rightPt) {
            int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt)) {
                rightPt = midPt - 1; ans = midPt;
            } else {
                leftPt = midPt + 1;
            }
        }
        cout << ans << '\n';
    }
 
    return 0;
}