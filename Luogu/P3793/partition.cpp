#include <bits/stdc++.h>
using namespace std;

namespace GenHelper {
    unsigned int z1, z2, z3, z4, b;
    unsigned int rand_() {
        b = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294u) << 18) ^ b;
        b = ((z2 << 2) ^ z2) >> 27;
        z2 = ((z2 & 4294967288u) << 2) ^ b;
        b = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280u) << 7) ^ b;
        b = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168u) << 13) ^ b;
        return (z1 ^ z2 ^ z3 ^ z4);
    }
}

void srand(unsigned int x) {
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333u; 
    z3 = x ^ 0x1234598766u; 
    z4 = (~x) + 51;
}

int read() {
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}

#define SIZE 20000010
#define BLK_NUM 5000
#define LG_SIZE 20

int arr[SIZE], pos[SIZE], blockSiz, blockNum, len;
int pfx[SIZE], sfx[SIZE], logs[SIZE], twoPows[30];
int stArr[BLK_NUM][LG_SIZE];

inline void initLogs() {
    logs[0] = -1;
    for (int i = 1; i < BLK_NUM; i++)
        logs[i] = logs[i >> 1] + 1;
    twoPows[0] = 1;
    for (int i = 1; i < 30; i++)
        twoPows[i] = twoPows[i - 1] << 1;
}

inline void initSt() {
    for (int b = 0, l = 0; l < len; b++, l += blockSiz) {
        int r = min(l + blockSiz, len) - 1;
        pfx[l] = arr[l]; sfx[r] = arr[r];
        for (int i = l + 1; i <= r; i++)
            pfx[i] = max(pfx[i - 1], arr[i]);
        for (int i = r - 1; i >= l; i--)
            sfx[i] = max(sfx[i + 1], arr[i]);
        stArr[b][0] = sfx[l];
    }

    int logLim = logs[blockNum];
    for (int j = 1; j <= logLim; j++) {
        for (int i = 0; i < blockNum; i++) {
            if (i + twoPows[j] - 1 >= blockNum)
                continue;
            stArr[i][j] = max(stArr[i][j - 1], stArr[i + twoPows[j - 1]][j - 1]);
        }
    }
}

inline int queryMax(int qLeftPt, int qRightPt) {
    if (pos[qLeftPt] == pos[qRightPt]) {
        int ret = arr[qLeftPt];
        for (int i = qLeftPt + 1; i <= qRightPt; i++)
            ret = max(ret, arr[i]);
        return ret;
    }

    int ret = max(sfx[qLeftPt], pfx[qRightPt]);
    qLeftPt = pos[qLeftPt] + 1, qRightPt = pos[qRightPt] - 1;
    if (qLeftPt > qRightPt)
        return ret; 
    int lenLog = logs[qRightPt - qLeftPt + 1];
    return max({ret, stArr[qLeftPt][lenLog], stArr[qRightPt - (1 << lenLog) + 1][lenLog]});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    initLogs();
    int qNum; unsigned int seed; unsigned long long int ans = 0;
    cin >> len >> qNum >> seed; srand(seed);
    blockSiz = max(1, (int)sqrt(len)); blockNum = len / blockSiz + (len % blockSiz > 0);
    for (int i = 0; i < len; i++)
        arr[i] = read(), pos[i] = i / blockSiz;
    initSt();

    while (qNum--) {
        int qLeftPt = read() % len, qRightPt = read() % len;
        if (qLeftPt > qRightPt)
            swap(qLeftPt, qRightPt);
        ans += queryMax(qLeftPt, qRightPt);
    }    

    cout << ans << '\n';
    return 0;
}