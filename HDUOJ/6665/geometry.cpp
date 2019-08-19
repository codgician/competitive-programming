#include <bits/stdc++.h>
using namespace std;

class Rect {
public:
    long long int xl, yl, xr, yr;
    void input() {
        cin >> xl >> yl >> xr >> yr;
        if (xl > xr) swap(xl, xr);
        if (yl > yr) swap(yl, yr);
    }
    long long int area() {
        return (xr - xl) * (yr - yl);
    }
    bool operator == (const Rect & snd) const {
        return xl == snd.xl && xr == snd.xr && yl == snd.yl && yr == snd.yr;
    }
};

Rect fst, snd;

int solve(Rect fst, Rect snd) {
    long long int xl = max(fst.xl, snd.xl), yl = max(fst.yl, snd.yl);
    long long int xr = min(fst.xr, snd.xr), yr = min(fst.yr, snd.yr);
    Rect inc = {xl, yl, xr, yr};

    if (xl > xr)
        return 3;
    if (yl > yr)
        return 3;
    long long int area = (xr - xl) * (yr - yl), cmp = min(fst.area(), snd.area());
    if (area == 0)
        return 3;
    if (area == cmp)
        return (fst.xl == snd.xl && fst.xr == snd.xr && min(fst.yl, snd.yl) != yl && max(fst.yr, snd.yr) != yr)
         || (fst.yl == snd.yl && fst.yr == snd.yr && min(fst.xl, snd.xl) != xl && max(fst.xr, snd.xr) != xr) ? 4 : 3;
    return solve(fst, inc) + solve(snd, inc) - 2; 
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        fst.input(); snd.input();
        if (fst == snd) {
            cout << 2 << '\n';
            continue;
        }
        cout << solve(fst, snd) << '\n';
    }

    return 0;
}