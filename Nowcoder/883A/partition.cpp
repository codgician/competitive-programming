#include <bits/stdc++.h>
using namespace std;
  
#define VERTEX_SIZE 100010
#define EDGE_SIZE 200020
#define SQRT_SIZE 100010
  
random_device rd;
mt19937 rng(rd());
uniform_int_distribution<long long int> unifLLInt(1, 1ll << 62);
  
typedef struct _Edge {
    int to, next;
} Edge;
  
Edge edge[EDGE_SIZE << 1];
int head[VERTEX_SIZE], edgePt, vertexNum, edgeNum;
long long int st[SQRT_SIZE], key[VERTEX_SIZE];
int bit[EDGE_SIZE], deg[VERTEX_SIZE], id[VERTEX_SIZE], lim, bigPt;
  
vector<pair<int, long long int> > vec[SQRT_SIZE];
  
void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}
  
int lowbit(int n) {
    return n & -n;
}
  
void add(int pos, int val) {
    pos++;
    for (int i = pos; i <= edgeNum + 1; i += lowbit(i))
        bit[i] ^= val;
}
  
int prefixSum(int pos) {
    int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret ^= bit[i];
    return ret;
}
  
void update(int leftPt, int rightPt) {
    add(leftPt, 1); add(rightPt + 1, 1);
  
    for (int i = 0; i < bigPt; i++) {
        auto & v = vec[i];
        auto lit = lower_bound(v.begin(), v.end(), make_pair(leftPt, -1ll));
        auto rit = lower_bound(v.begin(), v.end(), make_pair(rightPt + 1, -1ll));
      
        if (rit == v.begin())
            continue;
        rit = prev(rit); long long int contrib = rit -> second;
        if (lit != v.begin())
            contrib ^= prev(lit) -> second;
        st[i] ^= contrib;
    }
}
  
long long int query(int cntPt) {
    if (deg[cntPt] > lim)
        return st[id[cntPt]];
  
    long long int ret = 0;
    for (int i = head[cntPt]; i != -1; i = edge[i].next) {
        int nextPt = edge[i].to;
        if (prefixSum(i >> 1))
            ret ^= key[nextPt];
    }
  
    return ret;
}
  
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
      
    for (int i = 0; i < VERTEX_SIZE; i++)
        key[i] = unifLLInt(rng);
  
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> vertexNum >> edgeNum;
        fill(head + 0, head + vertexNum, -1);
        fill(deg + 0, deg + vertexNum, 0);
        fill(bit + 0, bit + edgeNum + 5, 0);
        edgePt = 0; bigPt = 0; lim = 1000;
  
        for (int i = 0; i < edgeNum; i++) {
            int from, to; cin >> from >> to;
            from--; to--;
            addEdge(from, to); addEdge(to, from);
            add(i, 1); add(i + 1, 1);
            deg[from]++; deg[to]++;
        }
   
        for (int i = 0; i < vertexNum; i++) {
            if (deg[i] > lim) {
                id[i] = bigPt++;
                st[id[i]] = 0; vec[id[i]].clear();
            }
        }
   
        for (int i = 0; i < edgePt; i += 2) {
            int from = edge[i ^ 1].to, to = edge[i].to;
            if (deg[from] > lim)
                vec[id[from]].push_back(make_pair(i >> 1, key[to]));
            if (deg[to] > lim)
                vec[id[to]].push_back(make_pair(i >> 1, key[from]));
        }
   
        for (int i = 0; i < bigPt; i++) {
            auto & v = vec[i]; sort(v.begin(), v.end());
            for (int j = 1; j < (int)v.size(); j++)
                v[j].second ^= v[j - 1].second;
        }
  
        int qNum; cin >> qNum;
        while (qNum--) {
            int op, fst, snd; cin >> op >> fst >> snd;
            fst--; snd--;
            if (op == 1)
                update(fst, snd);
            else
                cout << (query(fst) == query(snd) ? 1 : 0);
        }
        cout << '\n';
    }
      
    return 0;
}