#include <bits/stdc++.h>
using namespace std;

#define SIZE 410

int arr[SIZE][SIZE], fstNum, sndNum;
int fstEx[SIZE], sndEx[SIZE];
int sndMatch[SIZE], sndNeed[SIZE], pre[SIZE];
bool sndVisited[SIZE];

void bfs(int fstId) {
    for (int i = 0; i < sndNum; i++) {
        sndVisited[i] = false;
        sndNeed[i] = INT_MAX;
        pre[i] = -1;
    }
    int cntSnd = -1;
    while (cntSnd == -1 || sndMatch[cntSnd] != -1) {
        int cntFst;
        if (cntSnd == -1) {
            cntFst = fstId;
        } else {
            cntFst = sndMatch[cntSnd];
            sndVisited[cntSnd] = true;
        }
        int minDelta = INT_MAX, minSnd = -1;
        for (int i = 0; i < sndNum; i++) {
            if (!sndVisited[i]) {
                if (sndNeed[i] > fstEx[cntFst] + sndEx[i] - arr[cntFst][i]) {
                    sndNeed[i] = fstEx[cntFst] + sndEx[i] - arr[cntFst][i];
                    pre[i] = cntSnd;
                }
                if (sndNeed[i] < minDelta) {
                    minDelta = sndNeed[i];
                    minSnd = i;
                }
            }
        }

        fstEx[fstId] -= minDelta;
        for (int i = 0; i < sndNum; i++) {
            if (sndVisited[i]) {
                fstEx[sndMatch[i]] -= minDelta;
                sndEx[i] += minDelta;
            } else {
                sndNeed[i] -= minDelta;
            }
        }
        cntSnd = minSnd;
    }

    while (cntSnd != -1) {
        if (pre[cntSnd] == -1)
            sndMatch[cntSnd] = fstId;
        else
            sndMatch[cntSnd] = sndMatch[pre[cntSnd]];
        cntSnd = pre[cntSnd];
    }
}

int hungarian() {
    for (int i = 0; i < sndNum; i++) {
        sndMatch[i] = -1;
        sndEx[i] = 0;
    }
    for (int i = 0; i < fstNum; i++) {
        fstEx[i] = arr[i][0];
        for (int j = 1; j < sndNum; j++)
            fstEx[i] = max(fstEx[i], arr[i][j]);
    }
    for (int i = 0; i < sndNum; i++)
        bfs(i);

    int ans = 0;
    for (int i = 0; i < sndNum; i++)
        if (sndMatch[i] != -1)
            ans += arr[sndMatch[i]][i];
    return ans;
}

long long int ability[SIZE]; int weight[SIZE];
long long int fst[SIZE], snd[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    fstNum = len; sndNum = len;
    for (int i = 0; i < len; i++)
        cin >> ability[i];
    for (int i = 0; i < len; i++)
        cin >> weight[i];
    for (int i = 0; i < len; i++)
        cin >> fst[i];
    for (int i = 0; i < len; i++)
        cin >> snd[i];


    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            arr[i][j] = 0;
            for (int k = 0; k < len; k++)
                if (fst[i] + snd[j] > ability[k])
                    arr[i][j] += weight[k];
        }
    }

    int ans = hungarian();
    cout << ans << '\n';

    return 0;
}