#include <bits/stdc++.h>
using namespace std;

#define SIZE 2010

map<pair<long long int, long long int>, long long int> mp;
long long int stArr[SIZE][20], arr[SIZE], pfx[SIZE], sfx[SIZE];
int cnt[SIZE], pos[SIZE], len, qNum, sel, blockNum, blockSiz;

long long int calc(long long int fst, long long int snd) {
    tie(fst, snd) = make_tuple(min(fst, snd), max(fst, snd));
    if (fst == -1)
        return snd;
    if (mp.find(make_pair(fst, snd)) != mp.end())
        return mp[make_pair(fst, snd)];
    cout << "? " << fst << " " << snd << endl;
    long long int ret; cin >> ret;
    assert(ret != -1);
    mp[make_pair(fst, snd)] = ret;
    return ret;
}

void initSt() {
    for (int b = 0, l = 0; l < len; b++, l += blockSiz) {
        int r = min(l + blockSiz, len) - 1;
        pfx[l] = arr[l]; sfx[r] = arr[r];
        for (int i = l + 1; i <= r; i++)
            pfx[i] = calc(pfx[i - 1], arr[i]);
        for (int i = r - 1; i >= l; i--)
            sfx[i] = calc(sfx[i + 1], arr[i]);
        stArr[b][0] = sfx[l];
    }

    int logLim = log2(blockNum);
    for (int j = 1; j <= logLim; j++) {
        for (int i = 0; i < blockNum; i++) {
            if (i + (1 << j) - 1 >= len)
                continue;
            stArr[i][j] = calc(stArr[i][j - 1], stArr[i + (1 << (j - 1))][j - 1]);
        }
    }
}

long long int query(int qLeftPt, int qRightPt) {
    if (pos[qLeftPt] == pos[qRightPt]) {
        long long int ret = arr[qLeftPt];
        for (int i = qLeftPt + 1; i <= qRightPt; i++)
            ret = calc(ret, arr[i]);
        return ret;
    }

    long long int ret = calc(sfx[qLeftPt], pfx[qRightPt]);
    qLeftPt = pos[qLeftPt] + 1, qRightPt = pos[qRightPt] - 1;
    while (qLeftPt <= qRightPt) {
        int cntLen = log2(qRightPt - qLeftPt + 1);
        ret = calc(ret, stArr[qLeftPt][cntLen]);
        qLeftPt += (1 << cntLen);
    }
    return ret;
}

int main() {
    cin >> len >> qNum >> sel;
    blockSiz = max(1, 2 * (int)log2(len)); 
    blockNum = len / blockSiz + (len % blockSiz > 0);
    for (int i = 0; i < len; i++)
        cin >> arr[i], pos[i] = i / blockSiz;
    initSt();

    while (qNum--) {
        cout << "next" << endl;
        for (int i = 0; i < sel; i++)
            cin >> cnt[i], cnt[i]--;
        sort(cnt + 0, cnt + sel);
        long long int ret = -1; int nextPt = 0;
        for (int i = 0; i < sel; i++) {
            if (cnt[i] > nextPt)
                ret = calc(ret, query(nextPt, cnt[i] - 1));
            nextPt = max(nextPt, cnt[i] + 1);
        }

        if (cnt[sel - 1] < len - 1)
            ret = calc(ret, query(cnt[sel - 1] + 1, len - 1));
        
        cout << "! " << ret << endl;
    }

    return 0;
}