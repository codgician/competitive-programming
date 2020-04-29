#include <bits/stdc++.h>
using namespace std;

#define SIZE 21

long long int fst[SIZE], snd[SIZE], ans, lim;
vector<long long int> vec, sfx; int len;

void dfs(int pos, long long int sum) {
    if (sum >= lim) {
        ans += (1ll << (vec.size() - pos));
        return;
    }

    if (pos >= (int)vec.size() || sum + sfx[pos] < lim) 
        return;

    dfs(pos + 1, sum + vec[pos]);
    dfs(pos + 1, sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        cin >> len >> lim;
        for (int i = 0; i < len; i++)
            cin >> fst[i];
        for (int i = 0; i < len; i++)
            cin >> snd[i];

        ans = 0;
        for (int st = 0; st < (1 << len); st++) {
            long long int fstVal = 0, sndVal = 0, oneBit = 0;
            bitset<30> bst = st;
            for (int i = 0; i < len; i++)
                fstVal += bst[i] * fst[i], sndVal += (bst[i] ^ 1) * snd[i], oneBit += bst[i];
            if (fstVal < lim)
                continue;   // A is not happy
            if (sndVal >= lim) {
                ans += (1ll << oneBit);
                continue;
            }

            vec.clear(); sfx.clear();
            for (int i = 0; i < len; i++)
                if (bst[i])
                    vec.push_back(snd[i]);
            if ((int)vec.size() == 0)
                continue;
        
            sort(vec.begin(), vec.end(), greater<int>());
            sfx.resize(vec.size());
            sfx[vec.size() - 1] = vec.back();
            for (int i = vec.size() - 2; i >= 0; i--)
                sfx[i] = sfx[i + 1] + vec[i];

            dfs(0, sndVal);
        }

        cout << "Case #" << t << ": " << ans << '\n'; 
    }

    return 0;
}