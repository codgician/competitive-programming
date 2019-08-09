#include <bits/stdc++.h>
using namespace std;

#define SIZE 220
#define EDGE_SIZE 80080
#define VERTEX_SIZE 440

/* Maximum Flow :: Dinic */

class Edge {
public:
    int to, next, cap;
};

Edge edges[EDGE_SIZE];
int head[VERTEX_SIZE], edgesPt;
int depth[VERTEX_SIZE], lastVis[VERTEX_SIZE], vertexNum;

void addEdge(int from, int to, int cap){
    edges[edgesPt] = {to, head[from], cap};
    head[from] = edgesPt++;
    edges[edgesPt] = {from, head[to], 0};
    head[to] = edgesPt++;
}

bool updateDepth(int startPt, int endPt) {
    memset(depth, -1, sizeof(depth));
    queue<int> q;
    depth[startPt] = 0;
    q.push(startPt);
    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            if (depth[nextPt] == -1 && edges[i].cap > 0) {
                depth[nextPt] = depth[cntPt] + 1;
                if (nextPt == endPt)
                    return true;
                q.push(nextPt);
            }
        }
    }
    return false;
}

int findAugPath(int cntPt, int endPt, int minCap) {
    if (cntPt == endPt)
        return minCap;
    int cntFlow = 0;
    for (int & i = lastVis[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (depth[nextPt] == depth[cntPt] + 1 && edges[i].cap > 0) {
            int flowInc = findAugPath(nextPt, endPt, min(minCap - cntFlow, edges[i].cap));
            if (flowInc == 0) {
                depth[nextPt] = -1;
            } else {
                edges[i].cap -= flowInc;
                edges[i ^ 1].cap += flowInc;
                cntFlow += flowInc;
                if (cntFlow == minCap)
                    break;
            }
        }
    }
    return cntFlow;
}

int dinic(int srcPt, int snkPt) {
    int ans = 0;
    while (updateDepth(srcPt, snkPt)) {
        for (int i = 0; i < vertexNum; i++)
            lastVis[i] = head[i];
        int flowInc =  findAugPath(srcPt, snkPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

class Rect {
public:
    int xl, yl, xr, yr;
};

Rect arr[SIZE];

vector<int> xs, ys;
bool vis[SIZE][SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, num; cin >> len >> num;
    xs.push_back(1); xs.push_back(len + 1);
    ys.push_back(1); ys.push_back(len + 1);
    for (int i = 0; i < num; i++) {
        cin >> arr[i].xl >> arr[i].yl >> arr[i].xr >> arr[i].yr;
        xs.push_back(arr[i].xl); xs.push_back(arr[i].xr + 1); 
        ys.push_back(arr[i].yl); ys.push_back(arr[i].yr + 1);
    }

    sort(xs.begin(), xs.end()); sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int xLen = xs.size(), yLen = ys.size();
    vertexNum = xLen + yLen - 2;
    int srcPt = vertexNum++, snkPt = vertexNum++;
    fill(head + 0, head + vertexNum, -1); edgesPt = 0;
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < xLen - 1; i++)
        addEdge(srcPt, i, xs[i + 1] - xs[i]);
    for (int j = 0; j < yLen - 1; j++)
        addEdge(xLen - 1 + j, snkPt, ys[j + 1] - ys[j]);
    for (int i = 0; i < num; i++) {
        auto & rt = arr[i];
        int xlPt = lower_bound(xs.begin(), xs.end(), rt.xl) - xs.begin(), xrPt = lower_bound(xs.begin(), xs.end(), rt.xr + 1) - xs.begin();
        int ylPt = lower_bound(ys.begin(), ys.end(), rt.yl) - ys.begin(), yrPt = lower_bound(ys.begin(), ys.end(), rt.yr + 1) - ys.begin();
        for (int i = xlPt; i < xrPt; i++)
            for (int j = ylPt; j < yrPt; j++)
                vis[i][j] = true;
    }

    for (int i = 0; i < xLen - 1; i++)
        for (int j = 0; j < yLen - 1; j++)
            if (vis[i][j])
                addEdge(i, xLen - 1 + j, INT_MAX);

    int ans = dinic(srcPt, snkPt);
    cout << ans << '\n';

    return 0;
}