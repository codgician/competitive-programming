#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

class Node {
public:
    int id, x, y, val;
};

Node arr[SIZE];

bool onSeg(const Node & a, const Node & b, const Node & c) {
    return 1ll * (b.y - a.y) * (c.x - a.x) == 1ll * (c.y - a.y) * (b.x - a.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> arr[i].x >> arr[i].y >> arr[i].val;
        arr[i].id = i + 1;
    }
    sort(arr + 0, arr + len, [](const Node & fst, const Node & snd) {
        return fst.val > snd.val;
    });

    long long int ans = arr[0].val + arr[1].val;
    vector<int> vec; vec.push_back(arr[0].id); vec.push_back(arr[1].id);
    for (int i = 2; i < len; i++) {
        if (!onSeg(arr[0], arr[1], arr[i])) {
            ans += arr[i].val; vec.push_back(arr[i].id);
            break;
        }
    }

    cout << ans << '\n';
    for (int i = 0; i < 3; i++)
        cout << vec[i] << (i < 2 ? ' ' : '\n');

    return 0;
}