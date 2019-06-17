#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int fst[SIZE], snd[SIZE], ans[2][SIZE];
int fstLen, sndLen, ansLen[2];

void print(int id) {
    for (int i = ansLen[id] - 1; i >= 0; i--)
        cout << ans[id][i];
    cout << '\n';
}

bool cmp() {
    if (ansLen[0] < ansLen[1])
        return 0;
    if (ansLen[1] < ansLen[0])
        return 1;
    for (int i = ansLen[0]; i >= 0; i--) {
        if (ans[0][i] == ans[1][i])
            continue;
        if (ans[0][i] < ans[1][i])
            return 0;
        if (ans[1][i] < ans[0][i])
            return 1;
    }
    return 0;
}

void add(int id) {
    int maxLen = max(fstLen, sndLen);
    ansLen[id] = maxLen;
    for (int i = 0; i < maxLen; i++) {
        ans[id][i] += fst[i] + snd[i];
        if (ans[id][i] > 9) {
            ans[id][i + 1] += ans[id][i] / 10;
            ans[id][i] %= 10;
            if (i == maxLen - 1)
                ansLen[id]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; string str;
    cin >> len >> str;

    memset(fst, 0, sizeof(fst));
    memset(snd, 0, sizeof(snd));
    memset(ans, 0, sizeof(ans));

    int pos = len >> 1;
    int cntPos = pos;
    while (cntPos > 0 && str[cntPos] == '0')
        cntPos--;
    fstLen = cntPos; sndLen = len - fstLen;
    for (int i = 0; i < fstLen; i++)
        fst[fstLen - i - 1] = str[i] - '0';
    for (int i = 0; i < sndLen; i++)
        snd[sndLen - i - 1] = str[cntPos + i] - '0';
    add(0);

    memset(fst, 0, sizeof(fst));
    memset(snd, 0, sizeof(snd));
    cntPos = pos + 1;
    while (cntPos < len && str[cntPos] == '0')
        cntPos++;
    fstLen = cntPos; sndLen = len - fstLen;
    for (int i = 0; i < fstLen; i++)
        fst[fstLen - i - 1] = str[i] - '0';
    for (int i = 0; i < sndLen; i++)
        snd[sndLen - i - 1] = str[cntPos + i] - '0';
    add(1);

    int id = cmp();
    print(id);

    return 0;
}