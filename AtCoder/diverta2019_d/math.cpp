#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    long long int num, ans = 0;
    cin >> num;
    for (long long int i = 1; i * i <= num; i++) {
        if (num % i != 0)
            continue;
        if (i > 1 && num % (i - 1) != 0) {
            long long int cntAns = i - 1;
            if (num / cntAns == num % cntAns)
                ans += cntAns;
        }
        if (i * i != num && num / i > 1 && num % (num / i - 1) != 0) {
            long long int cntAns = num / i - 1;
            if (num / cntAns == num % cntAns)
                ans += cntAns;
        }
    }
    cout << ans << '\n';
    return 0;
}
