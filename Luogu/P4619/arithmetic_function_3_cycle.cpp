#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
const int mod = 1e9 + 7;

int primes[SIZE], minFac[SIZE], primesPt;
int numArr[SIZE], d[SIZE], dpfx[SIZE], mu[SIZE];

void init() {
    memset(minFac, 0, sizeof(minFac));
    primesPt = 0, d[1] = 1, mu[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFac[i] == 0) {
            mu[i] = -1, d[i] = 2, numArr[i] = 1;
            minFac[i] = i, primes[primesPt++] = i;
        }
        for (int j = 0; j < primesPt && primes[j] <= min(minFac[i], (SIZE - 1) / i); j++) {
            minFac[i * primes[j]] = primes[j];
            if (minFac[i] == primes[j]) {
                numArr[i * primes[j]] = numArr[i] + 1;
                d[i * primes[j]] = d[i] / (numArr[i] + 1) * (numArr[i * primes[j]] + 1);
                mu[i * primes[j]] = 0;
            } else {
                numArr[i * primes[j]] = 1;
                d[i * primes[j]] = d[i] * d[primes[j]];
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
    dpfx[0] = 0;
    for (int i = 1; i < SIZE; i++)
        dpfx[i] = (dpfx[i - 1] + d[i]) % mod;
}


vector<pair<int, int> > edges[SIZE];
vector<pair<pair<int, int>, int> > e;
int deg[SIZE], mark[SIZE], tmp[SIZE], a, b, c, maxv, minv;
long long int ans;

void addEdge(int from, int to, int val) {
    edges[from].push_back(make_pair(to, val));
}

void buildGraph() {
    fill(deg + 1, deg + maxv + 1, 0);
    fill(mark + 1, mark + maxv + 1, -1);
    for (const auto & p : e)
        deg[p.first.first]++, deg[p.first.second]++;
    int siz = e.size();
    for (int i = 0; i < siz; i++) {
        auto & p = e[i]; int fstPt = p.first.first, sndPt = p.first.second, val = p.second;
        if (deg[fstPt] > deg[sndPt] || (deg[fstPt] == deg[sndPt] && fstPt > sndPt))
            swap(fstPt, sndPt);
        addEdge(fstPt, sndPt, val);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); init();

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> a >> b >> c; ans = 0; e.clear();
        maxv = max({a, b, c}), minv = min({a, b, c});
        for (int i = 1; i <= maxv; i++)
            edges[i].clear();

        // Construct graph
        for (int l = 1; l <= maxv; l++) {
            if (mu[l] == 0)
                continue;
            vector<int> facs; int cnt = l;
            while (minFac[cnt] > 1) {
                int f = minFac[cnt]; facs.push_back(f);
                while (minFac[cnt] == f)
                    cnt /= f;
            }
            
            int siz = facs.size(), full = (1 << siz) - 1;
            for (int st = 0; st < (1 << siz); st++) {
                const auto getVal = [siz, facs](int st) {
                    int ret = 1;
                    for (int i = 0; st > 0; st >>= 1, i++)
                        if (st & 1)
                            ret *= facs[i];
                    return ret;
                };

                int rst = st ^ full, v = getVal(st);
                for (int subst = st; ; subst = st & (subst - 1)) {
                    int v1 = getVal(rst | subst);
                    if (v < v1)
                        e.push_back(make_pair(make_pair(v, v1), l));
                    if (subst == 0)
                        break;
                }
            }
        }
        buildGraph();

        // Three equvilants
        for (int i = 1; i <= minv; i++)
            if (mu[i] != 0)
                ans += 1ll * mu[i] * mu[i] * mu[i] * dpfx[a / i] * dpfx[b / i] * dpfx[c / i];

        // Two equvilants
        for (int fstPt = 1; fstPt <= maxv; fstPt++) {
            for (const auto & p : edges[fstPt]) {
                int sndPt = p.first, muProd = mu[fstPt] * mu[fstPt] * mu[sndPt];
                long long int cnt = 0;
                cnt += 1ll * dpfx[a / fstPt] * dpfx[b / p.second] * dpfx[c / p.second];
                cnt += 1ll * dpfx[a / p.second] * dpfx[b / fstPt] * dpfx[c / p.second];
                cnt += 1ll * dpfx[a / p.second] * dpfx[b / p.second] * dpfx[c / fstPt];
                ans += muProd * cnt;
                cnt = 0; muProd = mu[fstPt] * mu[sndPt] * mu[sndPt]; 
                cnt += 1ll * dpfx[a / sndPt] * dpfx[b / p.second] * dpfx[c / p.second];
                cnt += 1ll * dpfx[a / p.second] * dpfx[b / sndPt] * dpfx[c / p.second];
                cnt += 1ll * dpfx[a / p.second] * dpfx[b / p.second] * dpfx[c / sndPt];
                ans += muProd * cnt;
            }
        }

        // No equvilant
        for (int fstPt = 1; fstPt <= maxv; fstPt++) {
            if (mu[fstPt] == 0)
                continue;
            for (const auto & p : edges[fstPt])
                mark[p.first] = fstPt, tmp[p.first] = p.second;
            for (const auto & p : edges[fstPt]) {
                int sndPt = p.first, v1 = p.second;
                for (const auto & p1 : edges[sndPt]) {
                    int thdPt = p1.first, v2 = p1.second, v3 = tmp[thdPt];
                    int muProd = mu[fstPt] * mu[sndPt] * mu[thdPt];
                    if (mark[thdPt] == fstPt && muProd != 0) {
                        long long int cnt = 0;
                        cnt += 1ll * dpfx[a / v1] * dpfx[b / v2] * dpfx[c / v3];
                        cnt += 1ll * dpfx[a / v1] * dpfx[b / v3] * dpfx[c / v2];
                        cnt += 1ll * dpfx[a / v2] * dpfx[b / v1] * dpfx[c / v3];
                        cnt += 1ll * dpfx[a / v2] * dpfx[b / v3] * dpfx[c / v1];
                        cnt += 1ll * dpfx[a / v3] * dpfx[b / v1] * dpfx[c / v2];
                        cnt += 1ll * dpfx[a / v3] * dpfx[b / v2] * dpfx[c / v1];
                        ans += muProd * cnt;
                    }
                }
            }
        }
        cout << (ans + mod) % mod << '\n';
    }

    return 0;
}