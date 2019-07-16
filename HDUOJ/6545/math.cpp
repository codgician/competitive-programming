#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int num, sum;
    while (cin >> num) {
        int ans = 1; sum = num * (num + 1) / 2;
        for (int i = 2; i * i <= sum && ans == 1; i++)
            if (sum % i == 0)
                ans = sum / i;
        cout << ans << '\n';
    }

    return 0;
}