#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Node {
    int len, s, v;
} Node;

Node arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    while (cin >> len) {
        for (int i = 0; i <= len; i++)
            cin >> arr[i].len;
        for (int i = 0; i <= len; i++)
            cin >> arr[i].s;
        for (int i = 0; i <= len; i++)
            cin >> arr[i].v;

        double ans = (double)arr[0].s / arr[0].v, prev = 0;
        for (int i = 1; i <= len; i++) {
            prev += arr[i].len;
            ans = max(ans, (arr[i].s + prev) / arr[i].v);
        }

        cout << fixed << setprecision(6) << ans << '\n';
    }

    return 0;
}