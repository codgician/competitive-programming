#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

typedef struct _Query {
    int from, to, leftPt, rightPt;
} Query;

vector<Query> que;
int ans[SIZE];

stack<pair<int *, int> > stk;

int parent[SIZE], siz[SIZE], dep[SIZE];

pair<int, int> getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return make_pair(cntPt, 0);
    pair<int, int> ret = getParent(parent[cntPt]);
    ret.second ^= dep[cntPt];
    return ret;
}

bool merge(int fstPt, int sndPt) {
    pair<int, int> fst = getParent(fstPt), snd = getParent(sndPt);
    fstPt = fst.first, sndPt = snd.first;
    if (fstPt == sndPt)
        return false;
    if (siz[fstPt] < siz[sndPt])
        swap(fstPt, sndPt);

    stk.push(make_pair(parent + sndPt, parent[sndPt])); parent[sndPt] = fstPt;
    stk.push(make_pair(siz + fstPt, siz[fstPt])); siz[fstPt] += siz[sndPt];
    stk.push(make_pair(dep + sndPt, dep[sndPt])); dep[sndPt] = fst.second ^ snd.second ^ 1;
    return true;
}

void undo() {
    if (stk.empty())
        return;
    *stk.top().first = stk.top().second; stk.pop();
}

void divideConquer(int leftPt, int rightPt, const vector<Query> & vec) {
    int midPt = (leftPt + rightPt) >> 1, stkSiz = stk.size();
    vector<Query> leftVec, rightVec;
    for (int i = 0; i < (int)vec.size(); i++) {
        const Query & q = vec[i];
        if (q.leftPt == leftPt && q.rightPt == rightPt) {
            if (!merge(q.from, q.to) && getParent(q.from).second == getParent(q.to).second) {
                for (int i = leftPt; i <= rightPt; i++)
                    ans[i] = false;
                while ((int)stk.size() != stkSiz)
                    undo();
                return;    
            }
        } else {
            if (q.leftPt <= midPt)
                leftVec.push_back(Query{q.from, q.to, q.leftPt, min(q.rightPt, midPt)});
            if (q.rightPt > midPt)
                rightVec.push_back(Query{q.from, q.to, max(q.leftPt, midPt + 1), q.rightPt});
        }
    }

    if (leftPt == rightPt) {
        ans[leftPt] = true;
        while ((int)stk.size() > stkSiz)
            undo();
        return;
    }

    divideConquer(leftPt, midPt, leftVec);
    divideConquer(midPt + 1, rightPt, rightVec);
    while ((int)stk.size() > stkSiz)
        undo();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, qNum, timeLen;
    cin >> vertexNum >> qNum >> timeLen;
    for (int i = 0; i < vertexNum; i++)
        parent[i] = i, dep[i] = 0, siz[i] = 1;
    while (qNum--) {
        int from, to, leftPt, rightPt;
        cin >> from >> to >> leftPt >> rightPt; 
        from--; to--; leftPt++;
        if (leftPt > rightPt)
            continue;
        que.push_back(Query{from, to, leftPt, rightPt});
    }

    divideConquer(1, timeLen, que);
    for (int i = 1; i <= timeLen; i++)
        cout << (ans[i] ? "Yes\n" : "No\n");
    return 0;
}