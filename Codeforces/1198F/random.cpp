#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<int> vec, order;
int ans[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        int cnt; cin >> cnt;
        vec.push_back(cnt); order.push_back(i);
    }

    for (int t = 0; t < 200; t++) {
        shuffle(order.begin(), order.end(), rng);
        int fst = 0, snd = 0;
        for (int i = 0; i < len; i++) {
            if (fst != 1 && __gcd(fst, vec[order[i]]) != fst)
                fst = __gcd(fst, vec[order[i]]), ans[order[i]] = 1;
            else
                snd = __gcd(snd, vec[order[i]]), ans[order[i]] = 2;
        }

        if (fst == 1 && snd == 1) {
            cout << "YES\n";
            for (int i = 0; i < len; i++)
                cout << ans[i] << ' ';
            cout << '\n';
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}