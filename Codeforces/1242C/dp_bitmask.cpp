#include <bits/stdc++.h>
using namespace std;

#define SIZE 16

class Cycle {
public:
    int st; vector<int> v;
    Cycle() { st = 0; v.clear(); }
};

unordered_map<long long int, int> mp, visMp;
vector<Cycle> cycles;
long long int delta[SIZE];
int dp[1 << SIZE], pre[1 << SIZE];

vector<int> sel; pair<int, int> ans[SIZE];

void dfs(int st) {
    if (pre[st] <= 0) {
        sel.push_back(-pre[st]);
        return;
    }
    dfs(pre[st]); dfs(st ^ pre[st]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; long long int sum = 0; cin >> len;
    for (int i = 0; i < len; i++) {
        int num; long long int tot = 0; cin >> num;
        for (int j = 0; j < num; j++) {
            int cnt; cin >> cnt; 
            sum += cnt, tot += cnt;
            mp[cnt] = i;
        }
        delta[i] = tot;
    }

    if (sum % len != 0) {
        cout << "No\n";
        return 0;
    }

    long long int tgt = sum / len;
    for (int i = 0; i < len; i++)
        delta[i] = tgt - delta[i];

    // Find cycles
    for (const auto & p : mp) {
        if (visMp.find(p.first) != visMp.end())
            continue;

        visMp[p.first] = true;
        cycles.push_back(Cycle());
        auto & v = cycles.back().v; v.push_back(p.first);
        auto & mask = cycles.back().st;
        
        long long int val = p.first + delta[p.second]; int cntPt = p.second;
        mask |= 1 << cntPt;
        while (val != p.first) {
            if (mp.find(val) == mp.end() || mask & (1 << mp[val])) {
                cycles.pop_back(); break;
            }
            v.push_back(val); cntPt = mp[val]; visMp[val] = true;
            val += delta[cntPt]; mask |= 1 << cntPt;
        }
    }

    fill(dp + 0, dp + (1 << len), false);
    int siz = cycles.size();
    for (int i = 0; i < siz; i++) {
        const auto & c = cycles[i];
        dp[c.st] = true; pre[c.st] = -i; 
    }
    for (int st = 1; st < (1 << len); st++)
        for (int subst = st & (st - 1); subst > 0 && !dp[st]; subst = st & (subst - 1))
            if (dp[subst] && dp[st ^ subst])
                dp[st] = true, pre[st] = subst;
    
    if (!dp[(1 << len) - 1]) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";
    dfs((1 << len) - 1);
    for (const auto & s : sel) {
        const auto & v = cycles[s].v; int siz = v.size();
        for (int i = 0; i < siz; i++)
            ans[mp[v[(i + 1) % siz]]] = make_pair(v[(i + 1) % siz], mp[v[i]] + 1);
    }

    for (int i = 0; i < len; i++)
        cout << ans[i].first << " " << ans[i].second << '\n';
    return 0;
}
