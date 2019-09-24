#include <bits/stdc++.h>
using namespace std;

#define SIZE 10

vector<pair<int, int> > edges;
set<pair<int, int> > st; int vals[SIZE];

long long int power(long long int a, int n) {
    long long int ret = 1;
    for (int i = 0; i < n; i++)
        ret *= a;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int vertexNum, edgeNum; cin >> vertexNum >> edgeNum;
    for (int i = 0; i < edgeNum; i++) {
        int from, to; cin >> from >> to; from--; to--;
        edges.push_back(make_pair(from, to));
    }

    long long int lim = power(6, vertexNum); int ans = 0;
    for (int t = 0; t < lim; t++) {
        int cnt = t;
        for (int i = 0; i < vertexNum; i++) {
            vals[i] = cnt % 6 + 1;
            cnt /= 6;
        }

        st.clear();
        for (const auto & e : edges) {
            auto p = make_pair(vals[e.first], vals[e.second]);
            if (p.first > p.second)
                swap(p.first, p.second);
            st.insert(p);
        }
        ans = max(ans, (int)st.size());
    }
    cout << ans << '\n';
    return 0;
}