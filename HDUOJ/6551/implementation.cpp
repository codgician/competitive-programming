#include <bits/stdc++.h>
using namespace std;

#define SIZE 300010

const int cyc = 12 * 60 * 60;

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num; cin >> num;
    int h, m, s; cin >> h >> m >> s;
    int arrPt = 0, now = (h % 12) * 3600 + m * 60 + s;
    for (int i = 0; i < num; i++) {
        cin >> h >> m >> s;
        int cnt = (h % 12) * 3600 + m * 60 + s;
        if (cnt == now)
            continue;
        arr[arrPt++] = cnt;
        arr[arrPt++] = cnt + cyc;
        arr[arrPt++] = cnt + (cyc << 1);
    }

    sort(arr + 0, arr + arrPt);
    arrPt = unique(arr + 0, arr + arrPt) - arr;
    num = arrPt / 3;

    if (num == 0) {
        cout << "0.00\n";
        return 0;
    }

    int ans = INT_MAX;
    for (int i = 0; i + num - 1 < arrPt; i++) {
        int startPt = arr[i], endPt = arr[i + num - 1];
        if (startPt > now + cyc)
            ans = min(ans, endPt - (now + cyc));
        else if (endPt < now + cyc)
            ans = min(ans, now + cyc - startPt);
        else
            ans = min(ans, (now + cyc - startPt) * 2 + (endPt - (now + cyc)));
    }

    cout << ans * 6 << ".00\n";

    return 0;
}