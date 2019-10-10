#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE], siz[SIZE], edgesPt, ans;

void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}

void dfs(int cntPt, int fatherPt) {
    siz[cntPt] = 1; int fstMax = 0, sndMax = 0, sonNum = 0;
    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt); sonNum++;
        if (siz[nextPt] > fstMax) {
            sndMax = fstMax, fstMax = siz[nextPt];
        } else if (siz[nextPt] > sndMax) {
            sndMax = siz[nextPt];
        }
    }

    ans = max(ans, fstMax + sndMax + 1 + max(0, sonNum - 1 - (fatherPt == -1)));
    siz[cntPt] += fstMax + max(0, sonNum - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int vertexNum; cin >> vertexNum;
        fill(head + 0, head + vertexNum, -1); edgesPt = 0;
        for (int i = 1; i < vertexNum; i++) {
            int from, to; cin >> from >> to; from--; to--;
            addEdge(from, to); addEdge(to, from);
        }
        ans = 0; dfs(0, -1); cout << ans << '\n';   
    }

    return 0;
}