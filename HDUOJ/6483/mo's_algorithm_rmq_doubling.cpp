#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define DSC_SIZE 200010

typedef struct _Query {
    int id, qLeftPt, qRightPt;
} Query;

Query qArr[SIZE];
int arr[SIZE], posArr[SIZE], len;
pair<int, int> dsc[DSC_SIZE], st[SIZE][20];

int numArr[DSC_SIZE], cntId;
bool ans[SIZE];

pair<int, int> minMax(const pair<int, int> & fst, const pair<int, int> & snd) {
    return make_pair(min(fst.first, snd.first), max(fst.second, snd.second));
}

void initSt() {
    int logLim = log2(len);
    for (int i = 0; i < len; i++)
        st[i][0] = make_pair(arr[i], arr[i]);

    for (int j = 1; j <= logLim; j++) {
        for (int i = 0; i < len; i++) {
            if (i + (1 << j) - 1 >= len)
                continue;
            st[i][j] = minMax(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

pair<int, int> queryMinMax(int qLeftPt, int qRightPt) {
    int lenLog = log2(qRightPt - qLeftPt + 1);
    return minMax(st[qLeftPt][lenLog], st[qRightPt - (1 << lenLog) + 1][lenLog]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;

    int blockSize = sqrt(SIZE);
    for (int i = 0; i < SIZE; i++)
        posArr[i] = i / blockSize;

    while (caseNum--) {
        int qNum;
        cin >> len >> qNum;
        for (int i = 0; i < len; i++) {
            cin >> arr[i];
            dsc[i] = make_pair(arr[i], i);
        }
        sort(dsc + 0, dsc + len);

        arr[dsc[0].second] = 0;
        cntId = 0;
        for (int i = 1; i < len; i++) {
            if (dsc[i].first == dsc[i - 1].first + 1)
                cntId++;
            else if (dsc[i].first > dsc[i - 1].first + 1)
                cntId += 2;
            arr[dsc[i].second] = cntId;
        }

        initSt();

        for (int i = 0; i < qNum; i++) {
            cin >> qArr[i].qLeftPt >> qArr[i].qRightPt;
            qArr[i].qLeftPt--, qArr[i].qRightPt--;
            qArr[i].id = i;
        }

        sort(qArr + 0, qArr + qNum, [](const Query & fst, const Query & snd) {
            if (posArr[fst.qLeftPt] == posArr[snd.qLeftPt])
                return fst.qRightPt < snd.qRightPt;
            return posArr[fst.qLeftPt] < posArr[snd.qLeftPt];
        });
 
        for (int i = 0; i <= cntId + 1; i++)
            numArr[i] = 0;

        int cntLeftPt = 0, cntRightPt = 0, oneNum = 0;
        numArr[arr[0]] = 1;
        oneNum++;
        for (int i = 0; i < qNum; i++) {
            while (qArr[i].qLeftPt < cntLeftPt) {
                // Add left
                cntLeftPt--;
                int cntPt = cntLeftPt;
                if (numArr[arr[cntPt]] == 0) {
                    oneNum++;
                }
                numArr[arr[cntPt]]++;
            }
            
            while (qArr[i].qRightPt > cntRightPt) {
                // Add right
                cntRightPt++;
                int cntPt = cntRightPt;
                if (numArr[arr[cntPt]] == 0) {
                    oneNum++;
                }
                numArr[arr[cntPt]]++;
            }

            while (qArr[i].qLeftPt > cntLeftPt) {
                // Delete left
                int cntPt = cntLeftPt;
                if (numArr[arr[cntPt]] == 1) {
                    oneNum--;
                }
                numArr[arr[cntPt]]--;
                cntLeftPt++;
            }

            while (qArr[i].qRightPt < cntRightPt) {
                // Delete right
                int cntPt = cntRightPt;
                if (numArr[arr[cntPt]] == 1) {
                    oneNum--;
                }
                numArr[arr[cntPt]]--;
                cntRightPt--;
            }

            if (oneNum <= 1) {
                ans[qArr[i].id] = true;
                continue;
            }

            pair<int, int> range = queryMinMax(qArr[i].qLeftPt, qArr[i].qRightPt);
            if (oneNum == range.second - range.first + 1)
                ans[qArr[i].id] = true;
            else
                ans[qArr[i].id] = false;
        }

        for (int i = 0; i < qNum; i++) {
            cout << (ans[i] ? "YES\n" : "NO\n");
        }
    }

    return 0;
}