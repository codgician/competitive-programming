#include <bits/stdc++.h>
using namespace std;

#define SIZE 30

int num[SIZE]; vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        memset(num, 0, sizeof(num));
        string str; cin >> str;
        int cnt = 1; vec.clear();
        for (const auto & ch : str) {
            if (ch == '^') {
                vec.push_back(cnt); cnt = 1;
            } else {
                cnt++;
            }
        }
        vec.push_back(cnt);
        for (auto i : vec) {
            int pt = 0;
            while (i > 0) {
                num[pt++] += i & 1;
                i >>= 1;
            }
        }

        for (int i = 30; i >= 1; i--) {
            if (num[i] > 1) {
                num[i - 1] += (num[i] - 1) << 1;
                num[i] = 1;
            }
        }

        int ans = 0, qaq = 1;
        for (int i = 0; i < 30; i++) {
            if (num[i] & 1)
                ans ^= qaq;
            qaq <<= 1;
        }
        cout << ans << '\n';
    }

    return 0;
}