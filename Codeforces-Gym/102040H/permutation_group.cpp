#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 210
#define P_SIZE 50010
const int mod = 78294349;
 
long long int fastPow(long long int a, long long int n) {
	long long int ret = 1; a %= mod;
	while (n > 0) {
		if (n & 1)
			ret = (ret * a) % mod;
		a = (a * a) % mod; n >>= 1;
	}
	return ret;
}
 
int primes[P_SIZE], minFac[P_SIZE], primesPt;
void initPrimes() {
	memset(minFac, 0, sizeof(minFac)); primesPt = 0;
	for (int i = 2; i < P_SIZE; i++) {
		if (minFac[i] == 0) {
			minFac[i] = i;
			primes[primesPt++] = i;
		}
		for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (P_SIZE - 1) / i); j++) {
			minFac[i * primes[j]] = primes[j];
		}
	}
}
 
char ch[SIZE][SIZE];
int fst[SIZE][SIZE], snd[SIZE][SIZE], tmp[SIZE][SIZE], row, col;
pair<int, int> pos[SIZE * SIZE]; 
bool vis[SIZE * SIZE];
 
void print() {
	cerr << "print" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cerr << snd[i][j] << ' ';
		cerr << '\n';
	}
}
 
void rotate() {
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			tmp[i][j] = fst[i][j], snd[i][j] = 0;
 
	// Right
	for (int i = 0; i < row; i++) {
		int num = 0;
		for (int j = 0; j < col && tmp[i][j] != 0; j++)
			num++;
		for (int j = 0; j < num; j++)
			snd[i][col - num + j] = tmp[i][j];
	}
	// Up
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			tmp[i][j] = snd[i][j], snd[i][j] = 0;
	for (int j = 0; j < col; j++) {
		int num = 0;
		for (int i = row - 1; i >= 0 && tmp[i][j] != 0; i--)
			num++;
		for (int i = row - 1; i > row - 1 - num; i--)
			snd[num - row + i][j] = tmp[i][j];
	}
	// Left
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			tmp[i][j] = snd[i][j], snd[i][j] = 0;
	for (int i = 0; i < row; i++) {
		int num = 0;
		for (int j = col - 1; j >= 0 && tmp[i][j] != 0; j--)
			num++;
		for (int j = col - 1; j > col - 1 - num; j--)
			snd[i][num - col + j] = tmp[i][j];
	}	
	// Down
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			tmp[i][j] = snd[i][j], snd[i][j] = 0;
	for (int j = 0; j < col; j++) {
		int num = 0;
		for (int i = 0; i < row && tmp[i][j] != 0; i++)
			num++;
		for (int i = 0; i < num; i++)
			snd[row - num + i][j] = tmp[i][j]; 
	}
}
 
int main() {
	initPrimes(); 
	int caseNum; scanf("%d", &caseNum);
	for (int t = 1; t <= caseNum; t++) {
	 	scanf("%d%d", &row, &col);
		for (int i = 0; i < row; i++)
			scanf("%s", ch[i]);
		int id = 0;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				fst[i][j] = (ch[i][j] == '#' ? ++id : 0), snd[i][j] = 0;
		rotate();
		
		fill(vis + 1, vis + id + 2, false);
		for (int i = 0; i < row; i++) 
			for (int j = 0; j < col; j++) 
				if (fst[i][j] != 0)
					pos[fst[i][j]] = make_pair(i, j);
		
		map<int, int> mp; mp.clear();
		for (int i = 1; i <= id; i++) {
			if (vis[i]) continue;
			vis[i] = true;
			int cnt = 1, pt = snd[pos[i].first][pos[i].second];
			while (pt != i) {
				cnt++; vis[pt] = true;
				pt = snd[pos[pt].first][pos[pt].second];
			}
			while (minFac[cnt] > 1) {
				int p = minFac[cnt], exp = 1; cnt /= p;
				while (cnt % p == 0)
					cnt /= p, exp++;
				mp[p] = max(mp[p], exp);
			}
		}
		
		long long int ans = 1;
		for (const auto & p : mp)
			ans = ans * fastPow(p.first, p.second) % mod;
		printf("Case %d: %lld\n", t, ans);
	}
    return 0;
}