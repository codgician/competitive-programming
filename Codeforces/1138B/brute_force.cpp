#include <bits/stdc++.h>
using namespace std;

int arr[4], len;
string as, cs;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> len;
    cin >> cs >> as;

    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < len; i++) {
        int type = (cs[i] - '0') << 1 | (as[i] - '0');
        arr[type]++;
    }

    int cnst = arr[1] + arr[3] - (len >> 1);
    for (int a1 = 0; a1 <= arr[0]; a1++) {
        int d1 = a1 + cnst;
        if (d1 < 0 || d1 > arr[3])
            continue;
        for (int b1 = 0; b1 <= arr[1]; b1++) {
            int c1 = (len >> 1) - a1 - b1 - d1;
            if (c1 < 0 || c1 > arr[2])
                continue;

            for (int i = 0; i < len; i++) {
                int type = (cs[i] - '0') << 1 | (as[i] - '0');
                if (type == 0 && a1 > 0) {
                    cout << i + 1 << " ";
                    a1--;
                } else if (type == 1 && b1 > 0) {
                    cout << i + 1 << " ";
                    b1--;
                } else if (type == 2 && c1 > 0) {
                    cout << i + 1 << " ";
                    c1--;
                } else if (type == 3 && d1 > 0) {
                    cout << i + 1 << " ";
                    d1--;
                }
            }
            return 0;
        }
    }

    cout << -1 << endl;
    return 0;
}
