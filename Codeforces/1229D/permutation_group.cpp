#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010
#define FAC_SIZE 7
#define PERMU_SIZE 121
#define SUB_SIZE 210

vector<int> permus[PERMU_SIZE];
int mp[PERMU_SIZE][PERMU_SIZE], pos[PERMU_SIZE], arr[SIZE], factorials[FAC_SIZE], len, permusPt;
bool vis[PERMU_SIZE];

int id(const vector<int> & vec) {
    int ret = 0;
    for (int i = 0; i < len; i++) {
        int cnt = 0;
        for (int j = i + 1; j < len; j++)
            cnt += (vec[i] > vec[j]);
        ret += cnt * factorials[len - i - 1];
    }
    return ret;
}

vector<int> concat(const vector<int> & fst, const vector<int> & snd) {
    vector<int> ret; ret.resize(len);
    for (int i = 0; i < len; i++)
        ret[i] = fst[snd[i]];
    return ret;
}

void add(vector<int> & g, int e) {
    if (vis[e])
        return;
    int siz = g.size(), siz1 = siz;
    for (int i = 0; i < siz; i++) {
        const auto & v1 = g[i];
        int v2 = mp[v1][e];
        if (vis[v2])
            continue;
        for (int j = 0; j < siz1; j++) {
            int v3 = mp[v2][g[j]];
            g.push_back(v3); vis[v3] = true; siz++;
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; permusPt = 0; cin >> qNum >> len;
    vector<int> vec; factorials[0] = 1;
    for (int i = 0; i < len; i++)
        vec.push_back(i), factorials[i + 1] = factorials[i] * (i + 1);
    
    permus[permusPt++] = vec;
    while (next_permutation(vec.begin(), vec.end()))
        permus[permusPt++] = vec;
    for (int i = 0; i < permusPt; i++) {
        mp[i][i] = id(concat(permus[i], permus[i])); pos[i] = -1;
        for (int j = i + 1; j < permusPt; j++) {
            mp[i][j] = id(concat(permus[i], permus[j]));
            mp[j][i] = id(concat(permus[j], permus[i]));
        }
    }

    for (int i = 0; i < qNum; i++) {
        for (int j = 0; j < len; j++)
            cin >> vec[j], vec[j]--;
        arr[i] = id(vec);
    }

    long long int ans = 0; set<pair<int, int> > st;
    for (int i = 0; i < qNum; i++) {
        if (pos[arr[i]] != -1)
            st.erase(st.find(make_pair(pos[arr[i]], arr[i])));
        st.insert(make_pair(i, arr[i])); pos[arr[i]] = i;

        fill(vis + 0, vis + permusPt, false); vis[0] = true;
        vector<int> g = {0}; int prevPt = st.rbegin() -> first; add(g, st.rbegin() -> second);
        for (auto rit = next(st.rbegin()); rit != st.rend(); ++rit) {
            auto p = *rit;
            ans += (prevPt - p.first) * g.size();
            add(g, p.second); prevPt = p.first;
        }
        ans += (prevPt + 1) * g.size();
    }

    cout << ans << '\n';
    return 0;
}