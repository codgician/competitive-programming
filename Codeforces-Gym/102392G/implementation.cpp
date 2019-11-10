#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 110
 
class Block {
public:
    int x, y, z;
    bool operator < (const Block & snd) const {
        if (x != snd.x)
            return x < snd.x;
        if (y != snd.y)
            return y < snd.y;
        return z < snd.z;
    }
};
 
string fst[SIZE], snd[SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int n, m, h; cin >> n >> m >> h;
    for (int i = 0; i < n; i++)
        cin >> fst[i];
    for (int i = 0; i < n; i++)
        cin >> snd[i];
 
    bool flag = true;
    for (int i = 0; i < n && flag; i++) {
        auto & f = fst[i], & s = snd[i];
        int fsiz = 0, ssiz = 0;
        for (const auto & ch : f)
            fsiz += (ch == '1');
        for (const auto & ch : s)
            ssiz += (ch == '1');
        if (min(fsiz, ssiz) == 0 && max(fsiz, ssiz) != 0)
            flag = false;
    }
 
    if (!flag) {
        cout << -1 << '\n';
        return 0;
    }
 
    vector<Block> v;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < h; k++)
                if (fst[i][j] == '1' && snd[i][k] == '1')
                    v.push_back(Block{i, j, k});
 
    cout << v.size() << '\n';
    for (const auto & b : v)
        cout << b.x << ' ' << b.y << ' ' << b.z << '\n';
    v.clear();
 
    for (int i = 0; i < n; i++) {
        auto & f = fst[i], & s = snd[i];
        int fsiz = 0, ssiz = 0;
        for (const auto & ch : f)
            fsiz += (ch == '1');
        for (const auto & ch : s)
            ssiz += (ch == '1');
 
        if (fsiz <= ssiz) {
            int pt = h - 1, last;
            for (int j = m - 1; j >= 0; j--) {
                if (f[j] == '1') {
                    while (pt > 0 && s[pt] == '0')
                        pt--;
                    v.push_back(Block{i, j, pt--});
                    last = j;
                }
            }
 
            while (pt >= 0) {
                if (s[pt] == '1')
                    v.push_back(Block{i, last, pt});
                pt--;
            }
        } else {
            int pt = m - 1, last;
            for (int j = h - 1; j >= 0; j--) {
                if (s[j] == '1') {
                    while (pt > 0 && f[pt] == '0')
                        pt--;
                    v.push_back(Block{i, pt--, j});
                    last = j;
                }
            }
 
            while (pt >= 0) {
                if (f[pt] == '1')
                    v.push_back(Block{i, pt, last});
                pt--;
            }
        }
    }
 
    sort(v.begin(), v.end());
    cout << v.size() << '\n';
    for (const auto & b : v)
        cout << b.x << ' ' << b.y << ' ' << b.z << '\n';
    return 0;
}