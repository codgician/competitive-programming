#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

class LinkCutTree {
public:
    int val, maxv, maxPt; bool revLazy;
    int father, son[2];
};

LinkCutTree lct[SIZE];
stack<int> stk; 

const auto node = [](int rt) -> LinkCutTree & { return lct[rt]; };
const auto father = [](int rt) -> LinkCutTree & { return lct[node(rt).father]; };
const auto lson = [](int rt) -> LinkCutTree & { return lct[node(rt).son[0]]; };
const auto rson = [](int rt) -> LinkCutTree & { return lct[node(rt).son[1]]; };

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
    stk.push(cntPt);
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

typedef void (*fptr)(int, int, bool);
vector<pair<fptr, pair<int, int> > > ustk;
void undo() {
	if (ustk.empty())
		return;
	const auto & tp = ustk.back();
	(tp.first)(tp.second.first, tp.second.second, false);
	ustk.pop_back();
}

void link(int, int, bool);
void cut(int, int, bool);

void link(int from, int to, bool rec) {
    if (root(from) == root(to))
        return;
    evert(to);
    node(to).father = from;
	if (rec)
		ustk.push_back(make_pair(&cut, make_pair(from, to)));
}

void cut(int from, int to, bool rec) {
    evert(from);
    expose(to);
    splay(to);
    if (node(to).son[0] == from) {
        node(to).son[0] = 0;
        node(from).father = 0;
    }
	if (rec)
		ustk.push_back(make_pair(&link, make_pair(from, to)));
}

pair<int, int> query(int from, int to) {
    evert(from);
    expose(to);
    splay(to);
    return make_pair(node(to).maxv, node(to).maxPt);
}

void update(int cntPt, int val, bool rec) {
    splay(cntPt);
	if (rec)
		ustk.push_back(make_pair(&update, make_pair(cntPt, node(cntPt).val)));
    node(cntPt).val = val;
    pushUp(cntPt);
}

class Edge {
public:
	int from, to, val, tim;
};

vector<Edge> edges;

class Query {
public:
	int id, leftPt, rightPt;	// val = -1 means actual query
};

vector<Query> ques; int vertexNum;
unordered_map<long long int, int> mp;	// id

const auto p2ll = [](int x, int y) {
	if (x > y) swap(x, y);
	return 1ll * x * (vertexNum + 2) + y;
};

void divideConquer(int leftPt, int rightPt, const vector<Query> & vec) {
	int midPt = (leftPt + rightPt) >> 1, stkSiz = ustk.size();
	vector<Query> leftVec, rightVec;
	for (int i = 0; i < (int)vec.size(); i++) {
		const auto & q = vec[i];
		if (q.leftPt == leftPt && q.rightPt == rightPt) {
			const auto & e = edges[q.id];
			if (e.val != -1) {
				// Add edge into LCT
				if (root(e.from) == root(e.to)) {
					auto ret = query(e.from, e.to);
					if (e.val >= ret.first)
						continue;
					int id = ret.second - vertexNum - 1;
					cut(edges[id].from, ret.second, true);
					cut(ret.second, edges[id].to, true);
					update(ret.second, -1, true);
				}
				
				int pt = q.id + vertexNum + 1;
				update(pt, e.val, true);
				link(e.from, pt, true);
				link(pt, e.to, true);
			} else {
				if (root(e.from) != root(e.to)) {
					cout << -1 << '\n';
				} else {
					auto ret = query(e.from, e.to);
					cout << ret.first << '\n';
				}
			}
		} else {
			if (q.leftPt <= midPt)
				leftVec.push_back(Query{q.id, q.leftPt, min(q.rightPt, midPt)});
			if (q.rightPt > midPt)
				rightVec.push_back(Query{q.id, max(q.leftPt, midPt + 1), q.rightPt});
		}
	}
	
	if (leftPt == rightPt) {
		while ((int)ustk.size() != stkSiz)
			undo();
		return;
	}

	divideConquer(leftPt, midPt, leftVec);
	divideConquer(midPt + 1, rightPt, rightVec);
	while ((int)ustk.size() != stkSiz)
		undo();	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int qNum; cin >> vertexNum >> qNum;
	fill(lct + 0, lct + SIZE, LinkCutTree{0, -1, 0, 0, 0, {0, 0}});
	for (int i = 0; i < qNum; i++) {
		int op, from, to; cin >> op >> from >> to; from++; to++;
		if (from > to)
			swap(from, to);
		if (op == 0) {
			// New bridge
			int val; cin >> val;
			mp[p2ll(from, to)] = ques.size();
            ques.push_back(Query{(int)edges.size(), i, qNum - 1});
			edges.push_back(Edge{from, to, val, i});
		} else if (op == 1) {
			// Destroy bridge
            int id = mp[p2ll(from, to)];
            ques[id].rightPt = i - 1;
			mp[p2ll(from, to)] = -1;
		} else {
			ques.push_back(Query{(int)edges.size(), i, i});
			edges.push_back(Edge{from, to, -1 ,i});
		}
	}
    
    divideConquer(0, qNum - 1, ques);
	return 0;
}