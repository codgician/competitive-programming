#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 40010
 
/* Link/cut Tree */
 
class LinkCutTree {
public:
    int val, maxv, maxPt;
    bool revLazy;
    int father, son[2];
};
 
LinkCutTree lct[SIZE];
const LinkCutTree blankNode = {0, 0, 0, false, 0, {0, 0}};
 
const auto node = [](int rt) -> LinkCutTree & {
    return lct[rt];
};
const auto father = [](int rt) -> LinkCutTree & {
    return lct[node(rt).father];
};
const auto lson = [](int rt) -> LinkCutTree & {
    return lct[node(rt).son[0]];
};
const auto rson = [](int rt) -> LinkCutTree & {
    return lct[node(rt).son[1]];
};
 
void pushUp(int rt) {
    node(rt).maxv = node(rt).val; node(rt).maxPt = rt;
    for (int i = 0; i < 2; i++)
        if (node(rt).son[i] != 0)
            if (node(rt).maxv < node(node(rt).son[i]).maxv)
                node(rt).maxv = node(node(rt).son[i]).maxv, node(rt).maxPt = node(node(rt).son[i]).maxPt;
}
 
void pushDown(int rt) {
    if (!node(rt).revLazy)
        return;
    swap(node(rt).son[0], node(rt).son[1]);
    for (int i = 0; i < 2; i++)
        if (node(rt).son[i] != 0)
            node(node(rt).son[i]).revLazy ^= 1;
    node(rt).revLazy = false;
}
 
bool isRoot(int cntPt) {
    return father(cntPt).son[0] != cntPt && father(cntPt).son[1] != cntPt;
}
 
int whichSon(int cntPt) {
    return father(cntPt).son[1] == cntPt;
}
 
void rotate(int cntPt) {
    int fatherPt = node(cntPt).father, grandPt = node(fatherPt).father;
    int sonPt = node(cntPt).son[whichSon(cntPt) ^ 1];
 
    if (!isRoot(fatherPt))
        node(grandPt).son[whichSon(fatherPt)] = cntPt;
    if (whichSon(cntPt) == 0)
        node(cntPt).son[1] = fatherPt, node(fatherPt).son[0] = sonPt;
    else
        node(cntPt).son[0] = fatherPt, node(fatherPt).son[1] = sonPt;
    node(cntPt).father = grandPt;
    node(fatherPt).father = cntPt;
    if (sonPt != 0)
        node(sonPt).father = fatherPt;
    pushUp(fatherPt);
}
 
void splay(int cntPt) {
    stack<int> stk; stk.push(cntPt);
    while (!isRoot(stk.top()))
        stk.push(node(stk.top()).father);
    while (stk.size())
        pushDown(stk.top()), stk.pop();
    while (!isRoot(cntPt)) {
        if (!isRoot(node(cntPt).father))
            rotate(whichSon(cntPt) == whichSon(node(cntPt).father) ? node(cntPt).father : cntPt);
        rotate(cntPt);
    }
    pushUp(cntPt);
}
 
void expose(int cntPt) {
    int sonPt = 0;
    while (cntPt != 0) {
        splay(cntPt);
        node(cntPt).son[1] = sonPt;
        pushUp(cntPt);
        sonPt = cntPt;
        cntPt = node(cntPt).father;
    }
}
 
void evert(int cntPt) {
    expose(cntPt);
    splay(cntPt);
    node(cntPt).revLazy ^= 1;
}
 
int root(int cntPt) {
    expose(cntPt);
    splay(cntPt);
    while (node(cntPt).son[0] != 0) {
        pushDown(cntPt);
        cntPt = node(cntPt).son[0];
    }
    splay(cntPt);
    return cntPt;
}
 
void link(int from, int to) {
    if (root(from) == root(to))
        return;
    evert(to);
    node(to).father = from;
}
 
void cut(int from, int to) {
    evert(from);
    expose(to);
    splay(to);
    if (node(to).son[0] == from) {
        node(to).son[0] = 0;
        node(from).father = 0;
    }
}
 
pair<int, int> query(int from, int to) {
    evert(from);
    expose(to);
    splay(to);
    return make_pair(node(to).maxv, node(to).maxPt);
}
 
void update(int cntPt, int val) {
    splay(cntPt);
    node(cntPt).val = val;
    pushUp(cntPt);
}
 
/* Tree DP */
 
class Edge {
public:
    int to, next;
};
 
Edge edges[SIZE];
int head[SIZE], dp[SIZE], edgesPt, ret;
 
void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}
 
void dfs(int cntPt, int fatherPt) {
    dp[cntPt] = 0;
    for(int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        ret = max(ret, dp[cntPt] + dp[nextPt] + 1);
        dp[cntPt] = max(dp[cntPt], dp[nextPt] + 1);
    }
}
 
/* Divide and Conquer */
 
class Query {
public:
    int id, from, to, cost;
    int leftPt, rightPt;
};
 
vector<Query> que; bool vis[SIZE];
map<tuple<int, int, int>, vector<int> > mp;
int cntEdge, vertexNum, timeLen, quePt, ans[SIZE];
 
typedef void (* fptr)(int, int);
stack<pair<fptr, int> > stk;
 
void undo() {
    if (stk.empty())
        return;
    auto & p = stk.top();
    vis[p.second] ^= 1;
    (*p.first)(que[p.second].from, vertexNum + 1 + p.second);
    (*p.first)(vertexNum + 1 + p.second, que[p.second].to);
    stk.pop();
}
 
void divideConquer(int leftPt, int rightPt, const vector<Query> & vec) {
    int midPt = (leftPt + rightPt) >> 1, stkSiz = stk.size(), prev = cntEdge;
 
    vector<Query> leftVec, rightVec;
    for (const auto & q : vec) {
        if (q.leftPt == leftPt && q.rightPt == rightPt) {
            // Maintain MST
            if (root(q.from) == root(q.to)) {
                auto ret = query(q.from, q.to);
 
                if (q.cost > ret.first)
                    continue;
 
                int cutPt = ret.second - vertexNum - 1;
                cut(que[cutPt].from, ret.second); cut(ret.second, que[cutPt].to); vis[cutPt] = false;
                stk.push(make_pair(&link, cutPt));
                cntEdge--;
            }
 
            int pt = q.id + vertexNum + 1;
            update(pt, q.cost); vis[q.id] = true;
            link(q.from, pt); link(pt, q.to); cntEdge++;
            stk.push(make_pair(&cut, q.id));
        } else {
            if (q.leftPt <= midPt)
                leftVec.push_back(Query{q.id, q.from, q.to, q.cost, q.leftPt, min(q.rightPt, midPt)});
            if (q.rightPt > midPt)
                rightVec.push_back(Query{q.id, q.from, q.to, q.cost, max(q.leftPt, midPt + 1), q.rightPt});
        }
    }
 
    if (leftPt == rightPt) {
        if (cntEdge == vertexNum - 1) {
            ret = 0;
            fill(head + 0, head + vertexNum + 1, -1); edgesPt = 0;
            for (int i = 0; i < quePt; i++)
                if (vis[i]) 
                    addEdge(que[i].from, que[i].to), addEdge(que[i].to, que[i].from);
            dfs(1, 0);
            ans[leftPt] = ret;
        } else {
            ans[leftPt] = -1;
        }
 
        while ((int)stk.size() > stkSiz)
            undo();
        cntEdge = prev;
        return;
    }
 
    divideConquer(leftPt, midPt, leftVec);
    divideConquer(midPt + 1, rightPt, rightVec);
    while ((int)stk.size() > stkSiz)
        undo();
    cntEdge = prev;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    cin >> vertexNum >> timeLen; quePt = 0;
    fill(lct + 0, lct + vertexNum + timeLen + 1, blankNode);
    fill(vis + 0, vis + timeLen + 1, false);
    for (int i = 1; i <= timeLen; i++) {
        int type, from, to, cost;
        cin >> type >> from >> to >> cost;
         
        auto & v = mp[make_tuple(from, to, cost)];
        if (type == 1) {
            v.push_back(i);
        } else {
            que.push_back(Query{quePt++, from, to, cost, v.back(), i - 1});
            v.pop_back();
        }
    }
 
    for (auto & p : mp) {
        for (auto & i : p.second) {
            int from, to, cost; tie(from, to, cost) = p.first;
            que.push_back(Query{quePt++, from, to, cost, i, timeLen});
        }
    }
 
    cntEdge = 0;
    divideConquer(1, timeLen, que);
    for (int i = 1; i <= timeLen; i++)
        cout << ans[i] << '\n';
 
    return 0;
}