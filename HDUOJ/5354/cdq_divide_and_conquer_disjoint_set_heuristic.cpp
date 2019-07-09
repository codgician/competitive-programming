#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Edge {
    int to, next;
} Edge;

Edge edge[SIZE << 1];
int head[SIZE], edgePt;

int ans[SIZE];

void addEdge(int from, int to) {
    edge[edgePt] = {to, head[from]};
    head[from] = edgePt++;
}

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

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt) {
        ans[headPt] = 1;
        return;
    }

    int midPt = (headPt + tailPt) >> 1;
    bool hasOdd = false; unsigned int stkSize = stk.size();
    for (int i = headPt; i <= midPt && !hasOdd; i++) {
        for (int j = head[i]; j != -1 && !hasOdd; j = edge[j].next) {
            int nextPt = edge[j].to;
            if (nextPt >= midPt + 1 && nextPt <= tailPt)
                continue;
            if (!merge(i, nextPt) && getParent(i).second == getParent(nextPt).second)
                hasOdd = true;
        }
    }
    if (hasOdd)
        fill(ans + midPt + 1, ans + tailPt + 1, 0);
    else
        divideConquer(midPt + 1, tailPt);
    while (stk.size() > stkSize)
        undo();

    hasOdd = false;
    for (int i = midPt + 1; i <= tailPt && !hasOdd; i++) {
        for (int j = head[i]; j != -1 && !hasOdd; j = edge[j].next) {
            int nextPt = edge[j].to;
            if (nextPt >= headPt && nextPt <= midPt)
                continue;
            if (!merge(i, nextPt) && getParent(i).second == getParent(nextPt).second)
                hasOdd = true;
        }
    }
    if (hasOdd)
        fill(ans + headPt, ans + midPt + 1, 0);
    else
        divideConquer(headPt, midPt);
    while (stk.size() > stkSize)
        undo();    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int vertexNum, edgeNum; edgePt = 0;
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < vertexNum; i++)
            head[i] = -1, parent[i] = i, siz[i] = 1, dep[i] = 0;
        for (int i = 0; i < edgeNum; i++) {
            int from, to; cin >> from >> to;
            from--; to--;
            addEdge(from, to); addEdge(to, from);
        }

        divideConquer(0, vertexNum - 1);

        for (int i = 0; i < vertexNum; i++)
            cout << ans[i];
        cout << '\n';
    }

    return 0;
}