#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
 
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
 
class Query {
public:
    int from, to, leftPt, rightPt;
};
 
vector<Query> que;
vector<int> dsc, span;
int vertexNum, ans;
 
void divideConquer(int leftPt, int rightPt, const vector<Query> & vec) {
    int midPt = (leftPt + rightPt) >> 1, stkSiz = stk.size();
    vector<Query> leftVec, rightVec;
    for (int i = 0; i < (int)vec.size(); i++) {
        const Query & q = vec[i];
        if (q.leftPt == leftPt && q.rightPt == rightPt) {
            merge(q.from, q.to);
            if (getParent(1) == getParent(vertexNum)) {
                for (int i = leftPt; i <= rightPt; i++)
                    ans += span[i];
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
        if (getParent(1) == getParent(vertexNum))
            ans += span[leftPt];
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
 
    int qNum; cin >> vertexNum >> qNum;
    for (int i = 1; i <= vertexNum; i++)
        parent[i] = i, siz[i] = 1;
    for (int i = 0; i < qNum; i++) {
        int from, to, leftPt, rightPt; cin >> from >> to >> leftPt >> rightPt;
        que.push_back({from, to, leftPt, rightPt});
        dsc.push_back(leftPt); dsc.push_back(rightPt + 1);
    }
 
    sort(dsc.begin(), dsc.end());
    dsc.erase(unique(dsc.begin(), dsc.end()), dsc.end());
    for (int i = 0; i < (int)dsc.size() - 1; i++)
        span.push_back(dsc[i + 1] - dsc[i]);
    span.push_back(0);
 
    for (auto & q : que) {
        q.leftPt = lower_bound(dsc.begin(), dsc.end(), q.leftPt) - dsc.begin();
        q.rightPt = lower_bound(dsc.begin(), dsc.end(), q.rightPt + 1) - dsc.begin() - 1;
    }
 
    ans = 0;
    divideConquer(0, dsc.size() - 1, que);
    cout << ans << '\n';
 
    return 0;
}