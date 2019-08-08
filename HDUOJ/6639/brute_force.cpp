#include <bits/stdc++.h>
using namespace std;

#define SIZE 20

class Equ {
public:
    int x, y, k, t;
};

Equ arr[SIZE];
int fstLim[SIZE], sndLim[SIZE];
int num, lim;

bool check(int x, int y) {
    for (int i = 0; i < num; i++)
        if ((abs(x - arr[i].x) + abs(y - arr[i].y)) % arr[i].k != arr[i].t)
            return false;
    return true;
}

int __lcm(int fst, int snd) {
    return fst / __gcd(fst, snd) * snd;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    fstLim[0] = 0; sndLim[0] = 0;
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> num >> lim; lim++; int fstPt = 1, sndPt = 1, lcm = 1;
        for (int i = 0; i < num; i++) {
            cin >> arr[i].x >> arr[i].y >> arr[i].k >> arr[i].t;
            fstLim[fstPt++] = arr[i].x; sndLim[sndPt++] = arr[i].y;
            lcm = __lcm(lcm, arr[i].k);
        }
        fstLim[fstPt++] = lim; sndLim[sndPt++] = lim;
        sort(fstLim + 0, fstLim + fstPt); fstPt = unique(fstLim + 0, fstLim + fstPt) - fstLim;
        sort(sndLim + 0, sndLim + sndPt); sndPt = unique(sndLim + 0, sndLim + sndPt) - sndLim;
        long long int ans = 0;
        for (int i = 1; i < fstPt; i++) {
            for (int j = 1; j < sndPt; j++) {
                int fstLen = fstLim[i] - fstLim[i - 1], sndLen = sndLim[j] - sndLim[j - 1];
                for (int dx = 0; dx < min(fstLen, lcm); dx++) {
                    int x = fstLim[i - 1] + dx;
                    for (int dy = 0; dy < min(sndLen, lcm); dy++) {
                        int y = sndLim[j - 1] + dy;
                        if (check(x, y)) 
                            ans += 1ll * ((fstLim[i] - x - 1) / lcm + 1) * ((sndLim[j] - y - 1) / lcm + 1);
                    }
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}