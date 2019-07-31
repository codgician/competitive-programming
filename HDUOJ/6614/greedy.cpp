#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

unsigned int ans[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        unsigned int num, ret = 0; cin >> num;
        for (unsigned int i = 2; i <= num; i++) {
            ans[i] = 1u << (__builtin_ffs(~i) - 1);
            if (ans[i] > num)
                ans[i] = 1;
            ret += i & ans[i];
        }
        cout << ret << '\n' << ans[2];
        for (unsigned int i = 3; i <= num; i++)
            cout << ' ' << ans[i];
        cout << '\n';
    }

    return 0;
}
