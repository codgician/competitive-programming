#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

typedef struct _Query {
    int from, to, leftPt, rightPt;
} Query;
vector<Query> que;

map<pair<int, int>, vector<pair<int, int> > > mp;
long long int ans[SIZE], val;

/* Disjoint Set */

int parent[SIZE << 1], siz[2][SIZE << 1], qNum;
stack<pair<int *, int> > stk;

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return cntPt;
    return getParent(parent[cntPt]);
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    if (siz[0][fstPt] + siz[1][fstPt] < siz[0][sndPt] + siz[1][fstPt])
        swap(fstPt, sndPt);

    stk.push(make_pair(parent + sndPt, parent[sndPt])); parent[sndPt] = fstPt;
    for (int t = 0; t < 2; t++) {
        stk.push(make_pair(siz[t] + fstPt, siz[t][fstPt]));
        siz[t][fstPt] += siz[t][sndPt];
    }
    return true;
}

void undo() {
    if (stk.empty())
        return;
    *stk.top().first = stk.top().second; stk.pop();
}

void divideConquer(int leftPt, int rightPt, const vector<Query> & vec) {
    int midPt = (leftPt + rightPt) >> 1, stkSiz = stk.size();
    long long int prev = val;
    vector<Query> leftVec, rightVec;
    for (const auto & q : vec) {
        if (q.leftPt == leftPt && q.rightPt == rightPt) {
            int from = getParent(q.from << 1), to = getParent(q.to << 1 | 1);
            if (from == to)
                continue;
            val -= 1ll * siz[0][from] * siz[1][from] + 1ll * siz[0][to] * siz[1][to]; 
            merge((q.from << 1), (q.to << 1 | 1));
            from = getParent(q.from << 1);
            val += 1ll * siz[0][from] * siz[1][from];
        } else {
            if (q.leftPt <= midPt)
                leftVec.push_back(Query{q.from, q.to, q.leftPt, min(q.rightPt, midPt)});
            if (q.rightPt > midPt)
                rightVec.push_back(Query{q.from, q.to, max(q.leftPt, midPt + 1), q.rightPt});
        }
    }

    if (leftPt == rightPt) {
        ans[leftPt] = val;
        while ((int)stk.size() != stkSiz)
            undo();
        val = prev;
        return;
    }

    divideConquer(leftPt, midPt, leftVec);
    divideConquer(midPt + 1, rightPt, rightVec);
    while ((int)stk.size() != stkSiz)
        undo();
    val = prev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; qNum = 0; val = 0; cin >> len;
    for (int i = 0; i < (SIZE << 1); i++)
        parent[i] = i, siz[i & 1][i] = 1, siz[(i & 1) ^ 1][i] = 0;

    for (int i = 0; i < len; i++) {
        int x, y; cin >> x >> y; x--; y--;
        auto & v = mp[make_pair(x, y)];
        if (v.size() == 0 || v.back().second != len - 1)
            v.push_back(make_pair(i, len - 1));
        else
            v.back().second = i - 1;
    }

    for (const auto & p : mp)
        for (const auto & p1 : p.second)
            que.push_back({p.first.first, p.first.second, p1.first, p1.second});

    divideConquer(0, len - 1, que);
    for (int i = 0; i < len; i++)
        cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}
