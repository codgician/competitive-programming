#include <bits/stdc++.h>
using namespace std;

const long long int inf = 1000000000000000000ll;

void simplify(__int128 & a, __int128 & b) {
    __int128 gcd = __gcd(a, b);
    a /= gcd; b /= gcd;
}

pair<__int128, __int128> solve(__int128 a, __int128 b, __int128 c, __int128 d) {
    simplify(a, b); simplify(c, d);
    __int128 left = a / b + 1, right = (c - 1) / d;
    if (left <= right)
        return make_pair(left, 1);
    if (a == 0)
        return make_pair(1, d / c + 1);
    if (a <= b && c <= d) {
        pair<__int128, __int128> ans = solve(d, c, b, a);
        swap(ans.first, ans.second);
        return ans;
    }

    __int128 t = a / b;
    pair<__int128, __int128> ans = solve(a % b, b, c - t * d, d);
    ans.first = ans.first + ans.second * t;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int num; __int128 b = (__int128)inf * 10;
        char ch; cin >> num >> ch; cin >> num;
        int b2 = num % 10;
        if (num == 0) {
            cout << "0 1\n";
            continue;
        }

        __int128 a = (__int128)num * 10; 
        auto ret1 = solve(a - 1, b, a + 5, b);   // round down
        auto ret2 = solve(a - 6, b, a + 1, b);      // round up

        const auto check = [b2](pair<__int128, __int128> & ret) {
            if (ret.second > 1e9) return false;
            __int128 fst = ret.first * inf * 10;
            fst /= ret.second;

            int c2 = (fst / 10) % 10, c1 = fst % 10;

            if (c2 == b2 && c1 < 5)
                return true;
            if (c2 == b2 - 1 && c1 >= 5)
                return true;
            return false;
        };

        if (check(ret1))
            cout << (long long int)ret1.first << ' ' << (long long int)ret1.second << '\n';
        else
            cout << (long long int)ret2.first << ' ' << (long long int)ret2.second << '\n';
    }

    return 0;
}
