#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 50010
#define EDGE_SIZE 100010

typedef struct _Edge {
    int from, to, len;
} Edge;

vector<Edge> vec[2];
int vertexNum, edgeNum, need;
int parent[VERTEX_SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return cntPt;
    parent[cntPt] = getParent(parent[cntPt]);
    return parent[cntPt];
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    parent[sndPt] = fstPt;
    return true;
}

pair<int, int> kruskal() {
    for (int i = 0; i < vertexNum; i++)
        parent[i] = i;
    int cntLen = 0, whiteNum = 0;
    unsigned int whitePt = 0, blackPt = 0;
    while (whitePt < vec[0].size() && blackPt < vec[1].size()) {
        if (vec[0][whitePt].len <= vec[1][blackPt].len) {
            if (merge(vec[0][whitePt].from, vec[0][whitePt].to)) {
                cntLen += vec[0][whitePt].len;
                whiteNum++;
            }
            whitePt++;
        } else {
            if (merge(vec[1][blackPt].from, vec[1][blackPt].to)) {
                cntLen += vec[1][blackPt].len;
            }
            blackPt++;
        }
    }

    while (whitePt < vec[0].size()) {
        if (merge(vec[0][whitePt].from, vec[0][whitePt].to)) {
            cntLen += vec[0][whitePt].len;
            whiteNum++;
        }
        whitePt++;
    }

    while (blackPt < vec[1].size()) {
        if (merge(vec[1][blackPt].from, vec[1][blackPt].to)) {
            cntLen += vec[1][blackPt].len;
        }
        blackPt++;
    }

    return make_pair(cntLen, whiteNum);
}

int check(int cntDelta) {
    for (auto & e : vec[0])
        e.len += cntDelta;
    pair<int, int> ret = kruskal();
    ret.first -= ret.second * cntDelta;
    for (auto & e : vec[0])
        e.len -= cntDelta;
    if (ret.second >= need)
        return ret.first;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> vertexNum >> edgeNum >> need;
    for (int i = 0; i < edgeNum; i++) {
        int from, to, len, color;
        cin >> from >> to >> len >> color;
        vec[color].push_back({from, to, len});
    }

    for (int t = 0; t < 2; t++) {
        sort(vec[t].begin(), vec[t].end(), [](const Edge & fst, const Edge & snd) {
            return fst.len < snd.len;
        });
    }

    int leftPt = -101, rightPt = 101, ans = -1;
    while (leftPt <= rightPt) {
        int midPt = (leftPt + rightPt) / 2;
        int ret = check(midPt);
        if (ret == -1) {
            rightPt = midPt - 1;
        } else {
            ans = ret;
            leftPt = midPt + 1;
        }
    }

    cout << ans << '\n';
    return 0;
}
