#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

long long int fastPow(long long int a, long long int n) {
    long long int ans = 1;
    while (n > 0) {
        if (n & 1)
            ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

int phi(int num) {
    int ret = num;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            ret -= ret / i;
            while (num % i == 0)
                num /= i;
        }
    }
    if (num > 1)
        ret -= ret / num;
    return ret;
}

vector<int> fac;

void getFac(int num) {
    fac.clear();
    for (int i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            fac.push_back(i);
            if (i * i != num)
                fac.push_back(num / i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int num;
    while (cin >> num) {
        if (num == -1)
            break;
        if (num == 0) {
            cout << "0\n";
            continue;
        }
        
        getFac(num);

        long long int ans = 0;
        for (auto i : fac)
            ans = ans + phi(num / i) * fastPow(3, i);

        if (num & 1)
            ans += num * fastPow(3, ((num - 1) >> 1) + 1);
        else
            ans += (num >> 1) * (fastPow(3, (num >> 1) + 1) + fastPow(3, num >> 1)); 

        cout << ans / (num << 1) << '\n';
 }
    return 0;
}
