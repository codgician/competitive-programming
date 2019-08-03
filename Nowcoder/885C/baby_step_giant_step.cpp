#include <bits/stdc++.h>
using namespace std;
    
long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}
 
unordered_map<long long int, int> mp;
    
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
        
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long int n, x0, a, b, p; int qNum;
        cin >> n >> x0 >> a >> b >> p >> qNum;
    
        if (a == 0) {
            while (qNum--) {
                long long int v; cin >> v;
                cout << (v == x0 ? 0 : v == b && n > 1 ? 1 : -1) << '\n';
            }
            continue;
        }
     
        if (a == 1) {
            if (b == 0) {
                while (qNum--) {
                    long long int v; cin >> v;
                    cout << (v == x0 ? 0 : -1) << '\n';
                }
                continue;
            }
   
            while (qNum--) {
                long long int v; cin >> v;
                long long int ans = (v - x0) * fastPow(b, p - 2, p) % p;
                ans = (ans + p) % p;
                cout << (ans >= n ? -1 : ans) << '\n';
            }
            continue;
        }
    
        if (x0 == 0 && b == 0) {
            while (qNum--) {
                long long int v; cin >> v;
                cout << (v == 0 ? 0 : -1) << '\n';
            }
            continue;
        }
  
        mp.clear(); long long int phip = p - 1;
        long long int t1 = sqrt(p * qNum) + 1, t2 = p / t1 + 1, tmp = 1;
        for (int j = 0; j < t1; j++) {
            if (mp.find(tmp) != mp.end())
                break;
            mp[tmp] = j; tmp = tmp * a % p;
        }
          
        while (qNum--) {
            long long int v, ans = LLONG_MAX; cin >> v;
            long long int orz = b * fastPow(a - 1, p - 2, p) % p;
            long long int b1 = (v + orz) % p * fastPow(x0 + orz, p - 2, p) % p;

            long long int inv = fastPow(a, phip - t1 % phip, p); tmp = b1;
            for (int i = 0; i <= t2; i++) {
                int j = mp.find(tmp) == mp.end() ? -1 : mp[tmp];
                if (j != -1) {
                    ans = 1ll * i * t1 + j; break;
                }
                tmp = tmp * inv % p;
            }

            cout << (ans >= n ? -1 : ans) << '\n';
        }
    }
    
    return 0;
}