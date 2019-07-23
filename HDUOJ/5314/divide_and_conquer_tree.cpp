#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], arr[SIZE], edgePt, vertexNum, lim;
bool vis[SIZE];
long long int ans;

int siz[SIZE], mx[SIZE], cntSiz, cntRoot, tmpPt;
vector<pair<int, int> > vec;

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
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

void upd(pair<int, int> & ret, const pair<int, int> & val) {
    ret.first = min(ret.first, val.first);
    ret.second = max(ret.second, val.second);
}

void getDist(int cntPt, int fatherPt, pair<int, int> val) {
    upd(val, make_pair(arr[cntPt], arr[cntPt]));
    if (val.second <= val.first + lim)
        vec.push_back(val);

    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (nextPt == fatherPt || vis[nextPt])
            continue;
        getDist(nextPt, cntPt, val);
    }
}

long long int solve(int cntPt, const pair<int, int> & val) {
    long long int ret = 0; vec.clear();
    getDist(cntPt, -1, val);
    sort(vec.begin(), vec.end());

    for (int i = 0; i < (int)vec.size(); i++) {
        int pos = lower_bound(vec.begin(), vec.end(), make_pair(vec[i].second - lim, 0)) - vec.begin();
        ret += i - pos;
    }

    return ret;
}

void divideConquer(int cntPt) {
    vis[cntPt] = true;
    ans += solve(cntPt, make_pair(arr[cntPt], arr[cntPt]));
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (vis[nextPt])
            continue;
        ans -= solve(nextPt, make_pair(arr[cntPt], arr[cntPt]));
    }

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
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> vertexNum >> lim;
        fill(head + 0, head + vertexNum, -1);
        fill(vis + 0, vis + vertexNum, false);
        edgePt = 0; ans = 0;
        for (int i = 0; i < vertexNum; i++)
            cin >> arr[i];
        for (int i = 1; i < vertexNum; i++) {
            int from, to; cin >> from >> to; from--; to--;
            addEdge(from, to); addEdge(to, from);
        }

        cntRoot = vertexNum;
        mx[cntRoot] = INT_MAX;
        cntSiz = vertexNum;
        findCore(0, -1);
        divideConquer(cntRoot);

        cout << ans * 2 << '\n';
    }
    return 0;
}