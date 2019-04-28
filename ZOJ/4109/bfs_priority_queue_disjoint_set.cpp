#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

typedef struct _Edge {
    int to, next;
} Edge;
Edge edge[SIZE << 1];
int head[SIZE], edgePt;
int vertexNum, edgeNum;

int arr[SIZE], arrPt;
bool vis[SIZE];

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

int parent[SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return cntPt;
    parent[cntPt] = getParent(parent[cntPt]);
    return parent[cntPt];
}

void merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt > sndPt)
        swap(fstPt, sndPt);
    parent[sndPt] = fstPt;
}

void bfs(int startPt) {
    arrPt = 0;
    priority_queue<int, vector<int>, greater<int> > pq;
    pq.push(startPt);
    vis[startPt] = true;

    while (!pq.empty()) {
        int cntPt = pq.top();
        pq.pop();
        arr[arrPt++] = cntPt;

        for (int i = head[cntPt]; i != -1; i = edge[i].next) {
            int nextPt = edge[i].to;
            if (vis[nextPt])
                continue;
            vis[nextPt] = true;
            pq.push(nextPt);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        edgePt = 0;
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i <= vertexNum; i++)
            head[i] = -1, parent[i] = i, vis[i] = false;

        for (int i = 0; i < edgeNum; i++) {
            int from, to;
            cin >> from >> to;
            from--, to--;
            addEdge(from, to);
            addEdge(to, from);
            merge(from, to);
        }

        int ans = 0;
        for (int i = 0; i < vertexNum; i++)
            if (getParent(i) == i)
                ans++;
        cout << ans << '\n';

        int rootPt = vertexNum++;
        for (int i = 0; i < vertexNum; i++)
            if (getParent(i) == i) {
                addEdge(rootPt, i); 
                addEdge(i, rootPt);
            }

        bfs(rootPt);
        for (int i = 1; i < arrPt; i++)
            cout << arr[i] + 1 << (i == arrPt - 1 ? '\n' : ' ');
    }

    return 0;
}
