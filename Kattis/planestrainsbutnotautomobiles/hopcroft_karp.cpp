#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE << 1], edgesPt; 
int fstMatch[SIZE], sndMatch[SIZE], fstDist[SIZE], sndDist[SIZE];
int fstNum, sndNum; bool sndVis[SIZE], vis[SIZE << 1];

void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}

bool canFind(int fstPt) {
    for (int i = head[fstPt]; i != -1; i = edges[i].next) {
        int sndPt = edges[i].to - fstNum; assert(sndPt >= 0);
        if (sndVis[sndPt] || sndDist[sndPt] != fstDist[fstPt] + 1)
            continue;
        sndVis[sndPt] = true;
        if (sndMatch[sndPt] == -1 || canFind(sndMatch[sndPt])) {
            fstMatch[fstPt] = sndPt;
            sndMatch[sndPt] = fstPt;
            return true;
        }
    }
    return false;
}

bool findAugPath() {
    bool flag = false; queue<int> q;
    fill(fstDist + 0, fstDist + fstNum, 0);
    fill(sndDist + 0, sndDist + sndNum, 0);
    for (int i = 0; i < fstNum; i++)
        if (fstMatch[i] == -1)
            q.push(i);
    while (!q.empty()) {
        int fstPt = q.front(); q.pop();
        for (int i = head[fstPt]; i != -1; i = edges[i].next) {
            int sndPt = edges[i].to - fstNum; assert(sndPt >= 0);
            if (sndDist[sndPt] != 0)
                continue;
            sndDist[sndPt] = fstDist[fstPt] + 1;
            if (sndMatch[sndPt] != -1) {
                fstDist[sndMatch[sndPt]] = sndDist[sndPt] + 1;
                q.push(sndMatch[sndPt]);
            } else {
                flag = true;
            }
        }
    }
    return flag;
}

int hopcroftKarp() {
    fill(fstMatch + 0, fstMatch + fstNum, -1);
    fill(sndMatch + 0, sndMatch + sndNum, -1);
    int ret = 0;
    while (findAugPath()) {
        fill(sndVis + 0, sndVis + sndNum, false);
        for (int i = 0; i < fstNum; i++)
            ret += (fstMatch[i] == -1 && canFind(i));
    }
    return ret;
}

vector<int> vec;

void bfs(int startPt) {
    const auto trans = [](int pt) {
        return pt >= fstNum ? pt - fstNum : pt;
    };

    queue<int> q; q.push(startPt); vis[startPt] = true;
    vec.push_back(trans(startPt));
    while (!q.empty()) {
        int cntPt = q.front(); q.pop();
        for (int i = head[cntPt]; i != -1; i = edges[i].next) {
            int nextPt = edges[i].to;
            int matchPt = nextPt >= fstNum ? sndMatch[trans(nextPt)] : fstMatch[nextPt];
            if (matchPt == -1 || matchPt == cntPt)
                continue;
            if (nextPt < fstNum)
                matchPt += fstNum;
            if (!vis[matchPt]) {
                vis[matchPt] = true; q.push(matchPt);
                vec.push_back(trans(matchPt));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum; cin >> vertexNum >> edgeNum;
    fill(head + 0, head + (vertexNum << 1), -1); edgesPt = 0;
    fstNum = vertexNum, sndNum = vertexNum;
    for (int i = 0; i < edgeNum; i++) {
        int from, to; cin >> from >> to; from--; to--; 
        addEdge(from, fstNum + to); addEdge(fstNum + to, from);
    }

    int ans = vertexNum - hopcroftKarp() - 1;
    cout << ans << '\n';
    if (ans == 0)
        return 0;

    fill(vis + 0, vis + fstNum + sndNum, false);
    for (int i = 0; i < fstNum; i++)
        if (fstMatch[i] == -1)
            vec.push_back(i);
    for (int i = 0; i < sndNum; i++)
        if (sndMatch[i] == -1)
            vec.push_back(i);
    for (int i = 0; i < fstNum; i++)
        if (!vis[i] && fstMatch[i] == -1)
            bfs(i);
    for (int i = 0; i < sndNum; i++)
        if (!vis[fstNum + i] && sndMatch[i] == -1)
            bfs(fstNum + i);

    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int siz = vec.size();
    for (int i = 0; i < siz; i++)
        cout << vec[i] + 1 << (i == siz - 1 ? '\n' : ' ');
    return 0;
}