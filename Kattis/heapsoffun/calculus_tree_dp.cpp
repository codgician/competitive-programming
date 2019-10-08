#include <bits/stdc++.h>
using namespace std;

#define SIZE 310
const int mod = 1e9 + 7;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

class Polyn {
public:
    vector<int> vec;
    Polyn(int siz = 0) { vec.resize(siz); }

    Polyn operator * (const Polyn & snd) const {
        Polyn ret(vec.size() + snd.vec.size() - 1); 
        for (int i = 0; i < (int)vec.size(); i++)
            for (int j = 0; j < (int)snd.vec.size(); j++)
                ret.vec[i + j] = (ret.vec[i + j] + 1ll * vec[i] * snd.vec[j] % mod) % mod;
        return ret;
    }

    Polyn integrate() {
        Polyn ret(vec.size() + 1);
        for (int i = 0; i < (int)vec.size(); i++)
            ret.vec[i + 1] = vec[i] * fastPow(i + 1, mod - 2, mod) % mod;
        return ret;
    }

    long long int calc(long long int x) {
        long long int ret = 0, xe = 1;
        for (int i = 0; i < (int)vec.size(); i++)
            ret = (ret + xe * vec[i] % mod) % mod, xe = xe * x % mod;
        return ret;
    }
};

class Edge {
public:
    int to, next;
};

Edge edges[SIZE << 1];
int head[SIZE], edgesPt;
Polyn func[SIZE]; int minv[SIZE], lim[SIZE];

void addEdge(int from, int to) {
    edges[edgesPt] = {to, head[from]};
    head[from] = edgesPt++;
}

void dfs(int cntPt, int fatherPt) {
    auto & v = func[cntPt].vec; v.resize(1); v[0] = 1;
    if (edges[head[cntPt]].to == fatherPt && edges[head[cntPt]].next == -1) {
        v.push_back(fastPow(mod - lim[cntPt], mod - 2, mod));
        return;
    }

    for (int i = head[cntPt]; i != -1; i = edges[i].next) {
        int nextPt = edges[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        func[cntPt] = func[cntPt] * func[nextPt];
        minv[cntPt] = min(minv[cntPt], minv[nextPt]);
    }

    func[cntPt] = func[cntPt].integrate();
    v[0] = func[cntPt].calc(minv[cntPt]) % mod;
    for (int i = 1; i < (int)v.size(); i++)
        v[i] = mod - v[i];    
    for (auto & i : v)
        i = i * fastPow(lim[cntPt], mod - 2, mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, rootPt = -1; cin >> vertexNum;
    fill(head + 0, head + vertexNum, -1); edgesPt = 0;
    for (int i = 0; i < vertexNum; i++) {
        int fatherPt; cin >> lim[i] >> fatherPt; fatherPt--; minv[i] = lim[i];
        if (fatherPt == -1) {
            rootPt = i;
        } else {
            addEdge(i, fatherPt); addEdge(fatherPt, i);
        }
    }

    dfs(rootPt, -1);
    cout << func[rootPt].vec[0] << '\n';
    return 0;
}