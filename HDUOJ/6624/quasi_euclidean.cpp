#include <bits/stdc++.h>
using namespace std;

void simplify(long long int & a, long long int & b) {
    long long int gcd = __gcd(a, b);
    a /= gcd; b /= gcd;
}

pair<long long int, long long int> solve(long long int a, long long int b, long long int c, long long int d) {
    long long int left = a / b + 1, right = (c - 1) / d;
    if (left <= right)
        return make_pair(left, 1);
    if (a == 0)
        return make_pair(1, d / c + 1);
    if (a <= b && c <= d) {
        pair<long long int, long long int> ans = solve(d, c, b, a);
        swap(ans.first, ans.second);
        return ans;
    }

    long long int t = a / b;
    pair<long long int, long long int> ans = solve(a % b, b, c - t * d, d);
    ans.first += ans.second * t;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int p, x; cin >> p >> x;
        auto ret = solve(x - 1, p, x, p);
        simplify(ret.first, ret.second);
        long long int y = ret.first, b = ret.second;
        long long int a = x * b - p * y;
        cout << a << '/' << b << '\n';
    }

    return 0;
}