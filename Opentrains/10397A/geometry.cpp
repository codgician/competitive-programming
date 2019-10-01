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

int solve(Rect fst, Rect snd) {
    long long int xl = max(fst.xl, snd.xl), yl = max(fst.yl, snd.yl);
    long long int xr = min(fst.xr, snd.xr), yr = min(fst.yr, snd.yr);
    Rect inc = {xl, yl, xr, yr};
    if (xl > xr)
        return 0;
    if (yl > yr)
        return 0;

    if (inc == fst)
        return 1;
    if (inc == snd)
        return 2;
    return 3;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        Rect fst, snd; fst.input(); snd.input();
        int ret = solve(fst, snd);
        if (ret == 0)
            cout << "Separate\n";
        else if (ret == 1)
            cout << "A in B\n";
        else if (ret == 2)
            cout << "B in A\n";
        else
            cout << "Intersect\n";
    }

    return 0;
}