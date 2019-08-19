#include <bits/stdc++.h>
using namespace std;

#define SIZE 55

/* Hungarian */

bool arr[SIZE][SIZE], sndVisited[SIZE];
int sndMatch[SIZE], fstMatch[SIZE];
int fstNum, sndNum;

bool canFind(int fstId) {
    for (int i = 0; i < sndNum; i++) {
        if (arr[fstId][i] && !sndVisited[i]) {
            sndVisited[i] = true;
            if (sndMatch[i] == -1 || canFind(sndMatch[i])) {
                sndMatch[i] = fstId;
                return true;
            }
        }
    }
    return false;
}

int hungarian() {
    int ans = 0;
    memset(sndMatch, -1, sizeof(sndMatch));
    for (int i = fstNum - 1; i >= 0; i--) {
        memset(sndVisited, false, sizeof(sndVisited));
        if (canFind(i))
            ans++;
    }
    return ans;
}

unsigned long long st[SIZE];

const int lim = 12510;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int num, len; cin >> num >> len;
        for (int i = 0; i < len; i++)
            st[i] = (1ll << len) - 1;
        for (int i = 0; i < num; i++) {
            string fst, snd; cin >> fst >> snd;
            for (int i = 0; i < len; i++) {
                unsigned long long cntst = 0;
                for (int j = 0; j < len; j++)
                    if (fst[i] == snd[j])
                        cntst |= 1ll << j;
                st[i] &= cntst;
            }
        }

        for (int i = 0; i < len; i++) 
            for (int j = 0; j < len; j++)
                arr[i][j] = (st[i] & (1ll << j)) ? true : false;

        fstNum = len, sndNum = len;
        int ret = hungarian();
        if (ret != len) {
            cout << -1 << '\n';
        } else {
            for (int i = 0; i < len; i++)
                fstMatch[sndMatch[i]] = i;
            cout << fstMatch[0] + 1;
            for (int i = 1; i < len; i++)
                cout << ' ' << fstMatch[i] + 1;
            cout << '\n';
        }
    }

    return 0;
}
