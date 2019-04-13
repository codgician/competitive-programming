#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define DSC_SIZE 200010

typedef struct _Query {
    int id, qLeftPt, qRightPt;
} Query;

Query qArr[SIZE];
int arr[SIZE], posArr[SIZE];
pair<int, int> dsc[DSC_SIZE];

int numArr[DSC_SIZE], bit[DSC_SIZE], cntId;
bool ans[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i <= cntId + 1; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    pos++;
    int ans = 0;
    for (int i = pos; i > 0; i -= lowbit(i))
        ans += bit[i];
    return ans;
}

int getOnePos(int k) {
    int sum = 0, ans = 0;
    for (int i = 1 << 18; i > 0; i >>= 1) {
        ans += i;
        if (ans >= cntId + 1 || cnt + bit[ans] >= k)
            ans -= i;
        else
            cnt += bit[ans];
    }
    return ans + 1;
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
        int len, qNum;
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
            numArr[i] = 0, bit[i] = 0;

        int cntLeftPt = 0, cntRightPt = 0;
        numArr[arr[0]] = 1;
        add(arr[0], 1);
        for (int i = 0; i < qNum; i++) {
            while (qArr[i].qLeftPt < cntLeftPt) {
                // Add left
                cntLeftPt--;
                int cntPt = cntLeftPt;
                if (numArr[arr[cntPt]] == 0) {
                    add(arr[cntPt], 1);
                }
                numArr[arr[cntPt]]++;
            }
            
            while (qArr[i].qRightPt > cntRightPt) {
                // Add right
                cntRightPt++;
                int cntPt = cntRightPt;
                if (numArr[arr[cntPt]] == 0) {
                    add(arr[cntPt], 1);
                }
                numArr[arr[cntPt]]++;
            }

            while (qArr[i].qLeftPt > cntLeftPt) {
                // Delete left
                int cntPt = cntLeftPt;
                if (numArr[arr[cntPt]] == 1) {
                    add(arr[cntPt], -1);
                }
                numArr[arr[cntPt]]--;
                cntLeftPt++;
            }

            while (qArr[i].qRightPt < cntRightPt) {
                // Delete right
                int cntPt = cntRightPt;
                if (numArr[arr[cntPt]] == 1) {
                    add(arr[cntPt], -1);
                }
                numArr[arr[cntPt]]--;
                cntRightPt--;
            }

            int oneNum = prefixSum(cntId);
            if (oneNum <= 1) {
                ans[qArr[i].id] = true;
                continue;
            }

            int leftPt = getOnePos(1), rightPt = getOnePos(oneNum);
            leftPt--, rightPt--;

            if (prefixSum(rightPt) - prefixSum(leftPt - 1) == rightPt - leftPt + 1)
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