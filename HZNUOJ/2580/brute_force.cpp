#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010
#define TMP_SIZE 50

long long int arr[SIZE], tmp[TMP_SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, qNum;
    cin >> len >> qNum;
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    while (qNum--) {
        int qLeftPt, qRightPt;
        cin >> qLeftPt >> qRightPt;
        qLeftPt--, qRightPt--;
        if (qLeftPt > qRightPt) {
            cout << "NO\n";
            continue;
        }
        int len = qRightPt - qLeftPt + 1;
        if (len > 47) {
            cout << "YES\n";
            continue;
        }
        for (int i = qLeftPt; i <= qRightPt; i++)
            tmp[i - qLeftPt] = arr[i];
        sort(tmp + 0, tmp + len);
        bool ans = false;
        for (int i = 2; i < len; i++) {
            if (tmp[i - 2] + tmp[i - 1] > tmp[i]) {
                ans = true;
                break;
            }
        }

        if (ans)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}