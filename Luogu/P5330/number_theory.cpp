#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

int nxt[SIZE], arr[2][SIZE];
bool vis[SIZE], mark[SIZE];
pair<int, int> pos[SIZE];
vector<pair<int, long long int> > cycles[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int p, q, n, m; long long int t;
    cin >> p >> q >> n >> m >> t;

    int * fst = arr[0], * snd = arr[1];
    for (int i = 0; i < n; i++)
        cin >> fst[i];
    for (int i = 0; i < m; i++)
        cin >> snd[i];
    
    if (p > q) {
        swap(p, q); swap(n, m);
        swap(fst, snd);
    }

    int cyc = q / __gcd(p, q);
    for (int i = 0; i < q; i++) {
        nxt[i] = (i + p) % q;
        vis[i] = false, mark[i] = false;
    }

    for (int i = 0; i < m; i++)
        mark[snd[i]] = true;

    int cycNum = 0;
    for (int i = 0; i < q; i++) {
        if (vis[i])
            continue;
        int cntPt = i; cycles[cycNum].clear();
        while (!vis[cntPt]) {
            pos[cntPt] = make_pair(cycNum, cycles[cycNum].size());
            cycles[cycNum].push_back(make_pair(cntPt, mark[cntPt]));
            vis[cntPt] = true; cntPt = nxt[cntPt];
        }

        for (int j = 1; j < cyc; j++)
            cycles[cycNum][j].second += cycles[cycNum][j - 1].second;
        cycNum++;
    }
    
    long long int ans = 0;
    for (int i = 0; i < n; i++) {
        int v = fst[i]; long long int step = max(0ll, (t - 1 - v) / p + 1);
        if (step == 0)
            continue;
        const auto solve = [step, cyc, v]() {
            auto p = pos[v]; p.second = (p.second - 1 + cyc) % cyc; 
            long long int ret = (step / cyc) * cycles[p.first].back().second;
            int rem = step % cyc;
            if (p.second + rem < cyc) {
                ret += cycles[p.first][p.second + rem].second - cycles[p.first][p.second].second;
            } else {
                ret += cycles[p.first].back().second - cycles[p.first][p.second].second;
                ret += cycles[p.first][rem + p.second - cyc].second;
            }
            return ret;
        };
        ans += solve();
    }

    cout << ans << '\n';
    return 0;
}