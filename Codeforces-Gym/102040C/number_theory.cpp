#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 1000010
const int mod = 1e7 + 7;
 
int primes[SIZE], minFac[SIZE], primesPt;
void initPrimes() {
	memset(minFac, 0, sizeof(minFac)); primesPt = 0;
	for (int i = 2; i < SIZE; i++) {
		if (minFac[i] == 0) {
			minFac[i] = i;
			primes[primesPt++] = i;
		}
		for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
			minFac[i * primes[j]] = primes[j];
		}
	}
}
 
int solve(int n, int p) {
	if (n < p)
		return 0;
	return n / p + solve(n / p, p);
}
 
int main() {
	int num; initPrimes();
	while (cin >> num) {
		if (num == 0)
			break;
		vector<int> facs;
		for (int i = 0; i < primesPt && primes[i] <= num; i++)
			facs.push_back(solve(num, primes[i]));
		long long int ans = 1;
		for (const auto & i : facs) {
			const auto calc = [](int i) {
				return (1ll * i * (i + 1) / 2) % mod;
			};
			ans = ans * calc(i + 1) % mod;  
		}
		cout << ans << '\n';
	}
	return 0;
}