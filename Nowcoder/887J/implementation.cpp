#include <bits/stdc++.h>
using namespace std;

long long int reverse(long long int num) {
    long long int ret = 0;
    while (num > 0) {
        int cnt = num % 10;
        ret = ret * 10 + cnt;
        num /= 10;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int fst, snd; cin >> fst >> snd;
        fst = reverse(fst); snd = reverse(snd);
        long long int ans = fst + snd;
        cout << reverse(ans) << '\n';
    }

    return 0;
}