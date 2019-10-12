#include <bits/stdc++.h>
using namespace std;

#define SIZE 400010

stack<pair<int *, int> > stk;

int parent[SIZE], siz[SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return cntPt;
    return getParent(parent[cntPt]);
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    if (siz[fstPt] < siz[sndPt])
        swap(fstPt, sndPt);
    stk.push(make_pair(parent + sndPt, parent[sndPt])); parent[sndPt] = fstPt;
    stk.push(make_pair(siz + fstPt, siz[fstPt])); siz[fstPt] += siz[sndPt];
    return true;
}

void undo() {
    if (stk.empty())
        return;
    *stk.top().first = stk.top().second; stk.pop();
}

class Edge {
public:
    int op, from, to;
};
Edge edges[SIZE];

class Query {
public:
    int from, to, leftPt, rightPt;
};
vector<Query> ques; int vertexNum, last;
unordered_map<long long int, int> mp;
const auto p2ll = [](int x, int y) {
    tie(x, y) = make_tuple(min(x, y), max(x, y));
    return 1ll * x * SIZE + y; 
};

void divideConquer(int leftPt, int rightPt, const vector<Query> & vec) {
    int midPt = (leftPt + rightPt) >> 1, stkSiz = stk.size();
    const auto undoAll = [stkSiz]() { while ((int)stk.size() != stkSiz) undo(); };
    vector<Query> leftVec, rightVec;

    for (const auto & q : vec) {
        if (q.leftPt == leftPt && q.rightPt == rightPt) {
            if (!mp[p2ll(q.from, q.to)])
                continue;
            merge(q.from, q.to);
        } else {
            if (q.leftPt <= midPt)
                leftVec.push_back(Query{q.from, q.to, q.leftPt, min(q.rightPt, midPt)});
            if (q.rightPt > midPt)
                rightVec.push_back(Query{q.from, q.to, max(q.leftPt, midPt + 1), q.rightPt});
        }
    }
    
    if (leftPt == rightPt) {
        auto & e = edges[leftPt];
        e.from = (e.from + last) % vertexNum, e.to = (e.to + last) % vertexNum;
        
        if (e.op == 2) {
            last = (getParent(e.from) == getParent(e.to));
            cout << last;
        } else {
            mp[p2ll(e.from, e.to)] ^= 1;
        }
        undoAll();
        return;
    }

    divideConquer(leftPt, midPt, leftVec);
    divideConquer(midPt + 1, rightPt, rightVec);
    undoAll();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; cin >> vertexNum >> qNum;
    for (int i = 0; i < vertexNum; i++)
        parent[i] = i, siz[i] = 1;
    for (int i = 0; i < qNum; i++) {
        auto & e = edges[i]; cin >> e.op >> e.from >> e.to; e.from--; e.to--;
        const auto addQue = [i, qNum](int from, int to) {
            if (mp.find(p2ll(from, to)) == mp.end()) {
                if (i + 1 > qNum - 1)
                    return;
                mp[p2ll(from, to)] = ques.size();
                ques.push_back(Query{from, to, i + 1, qNum - 1});
            } else {
                ques[mp[p2ll(from, to)]].rightPt = max(ques[mp[p2ll(from, to)]].leftPt, i - 1);                    
                if (i + 1 > qNum - 1)
                    return;
                mp[p2ll(from, to)] = ques.size();
                ques.push_back(Query{from, to, i + 1, qNum - 1});
            }
        };

        if (e.op == 1) {
            int from = e.from, to = e.to;
            addQue(from, to);
            from = (from + 1) % vertexNum, to = (to + 1) % vertexNum;
            addQue(from, to);
        }
    }

    mp.clear(); last = 0;
    divideConquer(0, qNum - 1, ques);
    return 0;
}