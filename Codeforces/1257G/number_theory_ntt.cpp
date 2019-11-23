#include <bits/stdc++.h>
using namespace std;

#define SIZE 400010
const int mod = 998244353, pr = 3;

long long int fst[SIZE], snd[SIZE], omg[SIZE], inv[SIZE];
int arr[SIZE], pos[SIZE], fstLen, sndLen, len, lim;

long long int fastPow(long long int a, long long int n, long long int mod) {
    long long int ret = 1; a %= mod;
    while (n > 0) {
        if (n & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod; n >>= 1;
    }
    return ret;
}

void init() {
    len = 1, lim = 0;
    while (len < fstLen + sndLen - 1)
        len <<= 1, lim++;
    omg[0] = 1; inv[0] = 1; 
    long long int w =  fastPow(pr, (mod - 1) / len, mod);
    for (int i = 1; i < len; i++) {
        omg[i] = omg[i - 1] * w % mod;
        inv[len - i] = omg[i];
        pos[i] = (pos[i >> 1] >> 1) | ((i & 1) << (lim - 1));
    }
}

void ntt(long long int * arr, long long int * omg) {
    for (int i = 0; i < len; i++) 
        if (i < pos[i])
            swap(arr[i], arr[pos[i]]);
    for (int l = 2; l <= len; l <<= 1) {
        int midPt = l >> 1, step = len / l;
        for (long long int * p = arr; p != arr + len; p += l) {
            for (int i = 0, cnt = 0; i < midPt; i++, cnt += step) {
                long long int t = omg[cnt] * p[i + midPt] % mod;
                p[i + midPt] = (p[i] - t + mod) % mod; 
                p[i] = (p[i] + t) % mod;
            }
        }
    }
}

void multiply() {
    init(); int lenInv = fastPow(len, mod - 2, mod);
    ntt(fst, omg); ntt(snd, omg);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * snd[i] % mod;
    ntt(fst, inv);
    for (int i = 0; i < fstLen + sndLen - 1; i++)
        fst[i] = fst[i] * lenInv % mod;
    fill(fst + fstLen + sndLen - 1, fst + len, 0);
    fill(snd + fstLen + sndLen - 1, snd + len, 0);
}

vector<int> polyns[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    sort(arr + 0, arr + len);

    vector<pair<int, int> > v;
    v.push_back(make_pair(arr[0], 1));
    for (int i = 1; i < len; i++) {
        if (arr[i] == v.back().first) {
            v.back().second++;
        } else {
            v.push_back(make_pair(arr[i], 1));
        }
    }

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    int siz = v.size();
    for (int i = 0; i < siz; i++) {
        for (int j = 0; j <= min(len >> 1, v[i].second); j++)
            polyns[i].push_back(1);
        pq.push(make_pair(polyns[i].size(), i));
    }

    while (pq.size() > 1) {
        auto fstp = pq.top(); pq.pop();
        auto sndp = pq.top(); pq.pop();
        fstLen = fstp.first, sndLen = sndp.first;
        for (int i = 0; i < fstLen; i++)
            fst[i] = polyns[fstp.second][i];
        for (int i = 0; i < sndLen; i++)
            snd[i] = polyns[sndp.second][i];
        multiply();

        polyns[fstp.second].resize(min(len >> 1, fstLen + sndLen - 2) + 1); 
        for (int i = 0; i <= min(len >> 1, fstLen + sndLen - 2); i++)
            polyns[fstp.second][i] = fst[i], fst[i] = 0, snd[i] = 0;
        pq.push(make_pair(polyns[fstp.second].size(), fstp.second));
    }

    cout << polyns[pq.top().second][len >> 1] << '\n';
    return 0;
}
