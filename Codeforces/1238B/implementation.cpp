#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len, dist; cin >> len >> dist;
        for (int i = 0; i < len; i++)
            cin >> arr[i];
        sort(arr + 0, arr + len);

        int ret = 0, cntPt = len - 1;
        while (cntPt >= 0 && arr[cntPt] - ret * dist > 0) {
            int qaqPt = cntPt - 1;
            while (qaqPt >= 0 && arr[cntPt] == arr[qaqPt])
                qaqPt--;
            ret++; cntPt = qaqPt;
        }
        cout << ret << '\n';
    }

    return 0;
}