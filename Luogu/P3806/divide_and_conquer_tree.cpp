#include <bits/stdc++.h>
using namespace std;

#define SIZE 10010
#define Q_SIZE 110
#define LEN_SIZE 100000010

typedef struct _Edge {
    int to, next;
    int len;
} Edge;
Edge edge[SIZE << 1];
int head[SIZE], edgePt;
int vertexNum, qNum, cntSiz, cntRoot;

int qArr[Q_SIZE], siz[SIZE], mx[SIZE], dist[SIZE], rem[SIZE], remPt;
bool vis[SIZE], hasLen[LEN_SIZE], ans[Q_SIZE];

vector<int> delList;

void addEdge(int from, int to, int len) {
    edge[edgePt] = {to, head[from], len};
    head[from] = edgePt++;
}

void findCore(int cntPt, int fatherPt) {
    siz[cntPt] = 1, mx[cntPt] = 0;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt || vis[nextPt])
            continue;
        findCore(nextPt, cntPt);
        siz[cntPt] += siz[nextPt];
        mx[cntPt] = max(mx[cntPt], siz[nextPt]);
    } 
    mx[cntPt] = max(mx[cntPt], cntSiz - siz[cntPt]);
    if (mx[cntPt] < mx[cntRoot])
        cntRoot = cntPt;
}

void getDist(int cntPt, int fatherPt) {
    rem[remPt++] = dist[cntPt];
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt || vis[nextPt])
            continue;
        dist[nextPt] = dist[cntPt] + edge[i].len;
        getDist(nextPt, cntPt);
    }
}

void calc(int cntPt) {
    delList.clear();
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (vis[nextPt])
            continue;
        remPt = 0;
        dist[nextPt] = edge[i].len;
        getDist(nextPt, cntPt);

        for (int j = 0; j < remPt; j++)
            for (int k = 0; k < qNum; k++)
                if (qArr[k] >= rem[j])
                    ans[k] |= hasLen[qArr[k] - rem[j]];

        for (int j = 0; j < remPt; j++)
            hasLen[rem[j]] = true, delList.push_back(rem[j]);
    }

    for (auto i : delList)
        hasLen[i] = 0;
}

void divideConquer(int cntPt) {
    vis[cntPt] = true;
    hasLen[0] = true; 
    calc(cntPt);
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (vis[nextPt])
            continue;
        cntSiz = siz[nextPt];
        cntRoot = vertexNum;
        mx[cntRoot] = INT_MAX;
        findCore(nextPt, -1);
        divideConquer(cntRoot);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(head, -1, sizeof(head));
    memset(vis, false, sizeof(vis));
    memset(hasLen, false, sizeof(hasLen));
    memset(ans, false, sizeof(ans));
    edgePt = 0;
    cin >> vertexNum >> qNum;
    for (int i = 1; i < vertexNum; i++) {
        int from, to, len;
        cin >> from >> to >> len;
        from--, to--;
        addEdge(from, to, len);
        addEdge(to, from, len);
    }
    for (int i = 0; i < qNum; i++)
        cin >> qArr[i];

    cntRoot = vertexNum; 
    mx[vertexNum] = INT_MAX;
    cntSiz = vertexNum;
    findCore(0, -1);
    divideConquer(cntRoot);

    for (int i = 0; i < qNum; i++)
        cout << (ans[i] ? "AYE\n" : "NAY\n");
    return 0;
}