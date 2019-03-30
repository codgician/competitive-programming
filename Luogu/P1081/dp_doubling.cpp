#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define LOG_SIZE 20

int nextArr[SIZE][2], city[LOG_SIZE][SIZE][2], logLim;
long long int height[SIZE], length[2][LOG_SIZE][SIZE][2];

multiset<pair<long long int, int> > mst;

pair<long long int, int> calc(int pt, long long int lim) {
    pair<long long int, long long int> ret = make_pair(0, 0);
    for (int i = logLim; i >= 0; i--) {
        if (city[i][pt][1] == -1)
            continue;
        if (ret.first + ret.second + length[0][i][pt][1] + length[1][i][pt][1] <= lim) {
            ret.first += length[0][i][pt][1];
            ret.second += length[1][i][pt][1];
            pt = city[i][pt][1];
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(nextArr, -1, sizeof(nextArr));

    int vertexNum;
    cin >> vertexNum;
    logLim = log2(vertexNum) + 1;
    for (int i = 0; i < vertexNum; i++) {
        cin >> height[i];
        mst.insert(make_pair(height[i], i));
    }
    for (int i = 0; i < vertexNum; i++) {
        auto it = mst.lower_bound(make_pair(height[i], i));
        vector<pair<pair<long long int, long long int>, int> > vec;
        auto cntIt = it;
        for (int j = 0; cntIt != prev(mst.end()) && j < 2; j++) {
            cntIt = next(cntIt);
            pair<long long int, int> cnt = *cntIt;
            vec.push_back(make_pair(make_pair(llabs(cnt.first - height[i]), cnt.first), cnt.second));
        }
        cntIt = it;
        for (int j = 0; cntIt != mst.begin() && j < 2; j++) {
            cntIt = prev(cntIt);
            pair<long long int, int> cnt = *cntIt;
            vec.push_back(make_pair(make_pair(llabs(cnt.first - height[i]), cnt.first), cnt.second));
        }
        sort(vec.begin(), vec.end());
        for (int j = 0; j < min(2, (int)vec.size()); j++)
            nextArr[i][j] = vec[j].second;
        mst.erase(it);
    }

    memset(city, -1, sizeof(city));
    for (int j = 0; j < vertexNum; j++)
        for (int k = 0; k < 2; k++)
            city[0][j][k] = nextArr[j][k];
    for (int j = 0; j < vertexNum; j++)
        for (int k = 0; k < 2; k++)
            if (city[0][j][k] != -1)
                city[1][j][k] = city[0][city[0][j][k]][k ^ 1];
    for (int i = 2; i <= logLim; i++)
        for (int j = 0; j < vertexNum; j++)
            for (int k = 0; k < 2; k++)
                if (city[i - 1][j][k] != -1)
                    city[i][j][k] = city[i - 1][city[i - 1][j][k]][k];

    memset(length, 0, sizeof(length));
    for (int u = 0; u < 2; u++)
        for (int j = 0; j < vertexNum; j++)
            for (int k = 0; k < 2; k++)
                if (nextArr[j][u] != -1)
                    length[u][0][j][k] = (u == k ? llabs(height[j] - height[nextArr[j][u]]) : 0);
    for (int u = 0; u < 2; u++)
        for (int j = 0; j < vertexNum; j++)
            for (int k = 0; k < 2; k++)
                if (city[0][j][k] != -1)
                    length[u][1][j][k] = length[u][0][j][k] + length[u][0][city[0][j][k]][k ^ 1];
    for (int u = 0; u < 2; u++)
        for (int i = 2; i <= logLim; i++)
            for (int j = 0; j < vertexNum; j++)
                for (int k = 0; k < 2; k++)
                    if (city[i - 1][j][k] != -1)
                        length[u][i][j][k] = length[u][i - 1][j][k] + length[u][i - 1][city[i - 1][j][k]][k];
    

    long long int cntLim;
    int ansPt = -1;
    cin >> cntLim;
    double ratio = DBL_MAX;
    for (int i = 0; i < vertexNum; i++) {
        pair<long long int, long long int> cnt = calc(i, cntLim);
        double cntRatio = DBL_MAX;
        if (cnt.first != 0)
            cntRatio = (double)cnt.second / cnt.first;
        if (ansPt == -1 || ratio > cntRatio) {
            ratio = cntRatio;
            ansPt = i;
        } else if (ratio == cntRatio && height[i] > height[ansPt]) {
            ansPt = i;
        }
    }
    cout << ansPt + 1 << endl;

    int qNum;
    cin >> qNum;
    while (qNum--) {
        int startPt;
        cin >> startPt >> cntLim;
        startPt--;
        pair<long long int, long long int> ans = calc(startPt, cntLim);
        cout << ans.second << " " << ans.first << endl;
    }

    return 0;
}