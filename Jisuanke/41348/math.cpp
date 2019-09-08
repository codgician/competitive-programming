#include <bits/stdc++.h>
using namespace std;

#define SIZE 110
#define P_SIZE 2000010

int minFac[P_SIZE], primes[P_SIZE], phi[P_SIZE], primesPt;
int vis[P_SIZE];

void initPhi() {
    primesPt = 0; phi[1] = 1;
    for (int i = 2; i < P_SIZE; i++) {
        if (minFac[i] == 0) {
            minFac[i] = i; primes[primesPt++] = i;
            phi[i] = i - 1; vis[i] = 1;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (P_SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j])
                phi[i * primes[j]] = phi[i] * primes[j];
            else
                phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

int arr[SIZE];

int isPrime(int num) {
    if (num < P_SIZE)
        return vis[num];
    for (int i = 0; i < primesPt && primes[i] * primes[i] <= num; i++)
        if (num % primes[i] == 0)
            return false;
    return true;
}

int getPhi(int num) {
    if (num < P_SIZE)
        return phi[num];
    int ret = num;
    for (int i = 2; i * i <= num; i++) {
        if (num % i != 0)
            continue;
        ret -= ret / i;
        while (num % i == 0)
            num /= i;
    }
    if (num > 1)
        ret -= ret / num;
    return ret;
}

bool check(int pos) {
    for (int i = 0; i < 100; i++)
        if (arr[i] != getPhi(i + pos))
            return false;
    return true;
}

vector<int> mp[P_SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);    
    initPhi();
    for (int i = 1; i < P_SIZE; i++)
        mp[phi[i]].push_back(i);
    
   int caseNum; cin >> caseNum;
    while (caseNum--) {
        for (int i = 0; i < 100; i++)
            cin >> arr[i];
        int maxv = arr[0], maxPt = 0; bool flag = 0;
        for (int i = 1; i < 100; i++) {
            flag |= (arr[i] != 1 && (arr[i] & 1));
            if (arr[i] > maxv)
                maxv = arr[i], maxPt = i;
        }

        if (flag) {
            cout << "NO\n";
            continue;
        }

        if (isPrime(maxv + 1) && check(maxv - maxPt + 1)) {
            cout << "YES\n" << maxv - maxPt + 1 << '\n';
            continue;
        }

        int ans = -1; const int p = 83;
        for (int i = 0; i < 100 && ans == -1; i++) {
            if (arr[i] % (p - 1) != 0)
                continue;
            int rem = arr[i] / (p - 1);
            for (auto & v : mp[rem]) {
                if (check(p * v - i)) {
                    ans = p * v - i;
                    break;
                }
            }
        } 

        if (ans == -1) 
            cout << "NO\n";
        else
            cout << "YES\n" << ans << '\n';
    }

    return 0;
}