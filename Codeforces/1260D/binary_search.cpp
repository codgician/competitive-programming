#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

class Trap {
public:
    int loc, dism, dang;
};

Trap traps[SIZE];
int arr[SIZE], sfx[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int soldNum, len, trapNum, lim;
    cin >> soldNum >> len >> trapNum >> lim;
    for (int i = 0; i < soldNum; i++)
        cin >> arr[i];
    for (int i = 0; i < trapNum; i++)
        cin >> traps[i].loc >> traps[i].dism >> traps[i].dang;
    
    int leftPt = 0, rightPt = arr[soldNum - 1] + 1, ret;
    while (leftPt <= rightPt) {
        const auto check = [soldNum, len, trapNum, lim](int lb) {
            fill(sfx + 0, sfx + len + 2, INT_MAX);
            for (const auto & t : traps)
                if (t.dang > lb)
                    sfx[t.dism] = min(sfx[t.dism], t.loc);
            for (int i = len; i >= 0; i--)
                sfx[i] = min(sfx[i], sfx[i + 1]);
            int ret = 0;
            for (int i = 0; i <= len; i++)
                ret += sfx[i + 1] > i + 1 ? 1 : 3;
            return ret <= lim;
        };

        int midPt = (leftPt + rightPt) >> 1;
        if (check(midPt)) {
            rightPt = midPt - 1; ret = midPt;
        } else {
            leftPt = midPt + 1;
        }
    }

    cout << soldNum - (lower_bound(arr + 0, arr + soldNum, ret) - arr) << '\n';
    return 0;
}