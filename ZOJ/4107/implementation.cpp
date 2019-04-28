#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE];
bool isCrack[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(isCrack, false, sizeof(isCrack));
        int len, ans = 0;
        cin >> len;
        for (int i = 0; i < len; i++)
            cin >> arr[i];
        for (int i = 1; i < len - 1; i++)
            if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1])
                ans++, isCrack[i] = true;

        int delta = 0;
        for (int i = 1; i < len - 1; i++) {
            int cntDelta = 0;
            if (isCrack[i])
                cntDelta--;
            if (i - 1 > 0 && arr[i - 1] > arr[i - 2] && arr[i - 1] > arr[i + 1]) {
                if (!isCrack[i - 1]) {
                    cntDelta++;
                }
            } else if (i - 1 > 0 && isCrack[i - 1]) {
                cntDelta--;
            }

            if (i + 1 < len - 1 && arr[i + 1] > arr[i - 1] && arr[i + 1] > arr[i + 2]) {
                if (!isCrack[i + 1]) {
                    cntDelta++;
                }
            } else if (i + 1 < len - 1 && isCrack[i + 1]) {
                cntDelta--;
            }

            delta = min(delta, cntDelta);
        }

        cout << ans + delta << '\n';
    }

    return 0;
}
