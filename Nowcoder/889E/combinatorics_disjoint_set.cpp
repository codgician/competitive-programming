#include <bits/stdc++.h>
using namespace std;

const auto comb2 = [](long long int n) -> long long int {
    return n < 2 ? 0 : ((n & 1) ? ((n - 1) >> 1) * n : (n >> 1) * (n - 1));
};
const auto comb4 = [](long long int n) -> long long int {
    if (n < 4) return 0;
    long long int ret = comb2(n);
    ret = ret % 3 ? (n - 2) / 3 * ret : ret / 3 * (n - 2);
    ret = (ret & 3) ? ((n - 3) >> 2) * ret : (ret >> 2) * (n - 3);
    return ret;
};

#define SIZE 100010

int parent[SIZE], siz[SIZE], len;
long long int ans, sel2;

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt)
        return cntPt;
    parent[cntPt] = getParent(parent[cntPt]);
    return parent[cntPt];
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt), sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    if (siz[fstPt] < siz[sndPt])
        swap(fstPt, sndPt);

    sel2 -= comb2(siz[fstPt]) + comb2(siz[sndPt]);
    ans -= 1ll * siz[fstPt] * siz[sndPt] * (comb2(len - siz[fstPt] - siz[sndPt]) - sel2);
    parent[sndPt] = fstPt; siz[fstPt] += siz[sndPt];
    sel2 += comb2(siz[fstPt]);
    return true;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; cin >> len >> qNum;
    for (int i = 0; i < len; i++)
        parent[i] = i, siz[i] = 1;
    ans = comb4(len); sel2 = 0;
    cout << ans << '\n';
    while (qNum--) {
        int from, to; cin >> from >> to;
        from--; to--;
        merge(from, to);
        cout << ans << '\n';
    }

    return 0;
}