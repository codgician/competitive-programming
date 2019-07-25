#include <bits/stdc++.h>
using namespace std;
  
#define SIZE 300010
  
int arr[SIZE], len;
long long int pfx[SIZE], ans;
 
pair<int, int> stArr[SIZE][20];
 
void initSt() {
    int logLim = log2(len);
    for (int i = 0; i < len; i++)
        stArr[i][0] = make_pair(arr[i], i);
    for (int j = 1; j <= logLim; j++) {
        for (int i = 0; i < len; i++) {
            if (i + (1 << j) - 1 >= len)
                continue;
            stArr[i][j] = max(stArr[i][j - 1], stArr[i + (1 << (j - 1))][j - 1]);
        }
    }
}
 
pair<int, int> queryMax(int qLeftPt, int qRightPt) {
    int lenLog = log2(qRightPt - qLeftPt + 1);
    return max(stArr[qLeftPt][lenLog], stArr[qRightPt - (1 << lenLog) + 1][lenLog]);
}
  
long long int rangeSum(int qLeftPt, int qRightPt) {
    long long int ret = pfx[qRightPt];
    if (qLeftPt > 0)
        ret -= pfx[qLeftPt - 1];
    return ret;
}
  
void divideConquer(int headPt, int tailPt) {
    if (headPt >= tailPt)
        return;
 
    pair<int, int> ret = queryMax(headPt, tailPt);
    int maxv = ret.first, maxPt = ret.second;
 
    if (rangeSum(headPt, tailPt) >= (maxv << 1)) {
        if (maxPt - headPt < tailPt - maxPt) {
            for (int i = maxPt; i >= headPt; i--) {
                int leftPt = maxPt, rightPt = tailPt, ret = tailPt + 1;
                while (leftPt <= rightPt) {
                    int midPt = (leftPt + rightPt) >> 1;
                    if (rangeSum(i, midPt) >= (maxv << 1)) {
                        ret = midPt; rightPt = midPt - 1;
                    } else {
                        leftPt = midPt + 1;
                    }
                }
                ans += tailPt - ret + 1;
            }
        } else {
            for (int i = maxPt; i <= tailPt; i++) {
                int leftPt = maxPt, rightPt = headPt, ret = headPt - 1;
                while (leftPt >= rightPt) {
                    int midPt = (leftPt + rightPt) >> 1;
                    if (rangeSum(midPt, i) >= (maxv << 1)) {
                        ret = midPt; rightPt = midPt + 1;
                    } else {
                        leftPt = midPt - 1;
                    }
                }
                ans += ret - headPt + 1;
            }
        }
    }
  
    divideConquer(headPt, maxPt - 1);
    divideConquer(maxPt + 1, tailPt);
}
  
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
  
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> len;
        for (int i = 0; i < len; i++)
            cin >> arr[i];
        initSt();
        pfx[0] = arr[0];
        for (int i = 1; i < len; i++)
            pfx[i] = pfx[i - 1] + arr[i];
          
        ans = 0;
        divideConquer(0, len - 1);
        cout << ans << '\n';
    }
  
    return 0;
}