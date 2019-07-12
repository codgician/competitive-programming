#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 20010
#define EDGE_SIZE 50010

typedef struct _Query {
    int id, val;
} Query;

Query qArr[EDGE_SIZE];

typedef struct _Edge {
    int id, from, to, len;
    bool operator < (const struct _Edge & snd) const {
        return len < snd.len;
    }
} Edge;

vector<Edge> edge[30], ret, tmp;

int id[EDGE_SIZE], cntLen[EDGE_SIZE];
long long int ans[EDGE_SIZE];

/* Disjoint Set */

int parent[VERTEX_SIZE], siz[VERTEX_SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return cntPt;
    parent[cntPt] = getParent(parent[cntPt]);
    return parent[cntPt];
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt); sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    if (siz[fstPt] < siz[sndPt])
        swap(fstPt, sndPt);
    parent[sndPt] = fstPt;
    siz[fstPt] += siz[sndPt];
    return true;
}

void clear(const vector<Edge> & vec) {
    for (const auto & e : vec) {
        parent[e.from] = e.from;
        parent[e.to] = e.to;
        siz[e.from] = 1; siz[e.to] = 1;
    }
}

/* Divide And Conquer */

void relabel(vector<Edge> & vec) {
    int pt = 0;
    for (const auto & e : vec)
        id[e.id] = pt++;
}

void reduction() { 
    tmp.clear(); clear(ret); 
    sort(ret.begin(), ret.end());
    for (const auto & e : ret)
        if (e.len == INT_MAX || merge(e.from, e.to))
            tmp.push_back(e);

    relabel(tmp); ret = tmp;
}

void contraction(long long int & val) { 
    // Reduction
    tmp.clear(); clear(ret);
    sort(ret.begin(), ret.end());
    for (const auto & e : ret)
        if (merge(e.from, e.to)) 
            tmp.push_back(e);

    // Contraction
    clear(tmp); sort(tmp.begin(), tmp.end());
    for (const auto & e : tmp)
        if (e.len != INT_MIN && merge(e.from, e.to))
            val += e.len;
    tmp.clear();
    for (const auto & e : ret) {
        int from = getParent(e.from), to = getParent(e.to);
        tmp.push_back({e.id, from, to, e.len});
    }

    relabel(tmp); ret = tmp;
} 

void divideConquer(int headPt, int tailPt, int dep, long long int val) {
    if (headPt == tailPt)
        cntLen[qArr[headPt].id] = qArr[headPt].val; 

    // Recover
    ret = edge[dep]; relabel(ret);
    for (auto & e : ret)
        e.len = cntLen[e.id];

    if (headPt == tailPt) {
        ans[headPt] = val; clear(ret);
        sort(ret.begin(), ret.end());
        for (const auto & e : ret)
            if (merge(e.from, e.to))
                ans[headPt] += e.len;
        return;
    }

    for (int i = headPt; i <= tailPt; i++)
        ret[id[qArr[i].id]].len = INT_MIN;
    contraction(val);
    for (int i = headPt; i <= tailPt; i++)
        ret[id[qArr[i].id]].len = INT_MAX;
    reduction();

    // Pushdown
    edge[dep + 1] = ret;

    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt, dep + 1, val);
    divideConquer(midPt + 1, tailPt, dep + 1, val);
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum, qNum;
    cin >> vertexNum >> edgeNum >> qNum;
    for (int i = 0; i < edgeNum; i++) {
        int from, to, len; cin >> from >> to >> len;
        from--; to--; cntLen[i] = len;
        edge[0].push_back({i, from, to, len});
    }
    for (int i = 0; i < qNum; i++) {
        cin >> qArr[i].id >> qArr[i].val;
        qArr[i].id--;
    }

    divideConquer(0, qNum - 1, 0, 0);
    for (int i = 0; i < qNum; i++)
        cout << ans[i] << '\n';
    return 0;
}