#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string buf; int num;
    cin >> num;
    int ans = 0, leftNum = 0, rightNum = 0, tatNum = 0;
    for (int i = 0; i < num; i++) {
        cin >> buf;
        for (int i = 0; i < (int)buf.size() - 1; i++)
            if (buf[i] == 'A' && buf[i + 1] == 'B')
                ans++;
        if (buf[0] == 'B')
            rightNum++;
        if (buf[buf.size() - 1] == 'A')
            leftNum++;
        if (buf[0] == 'B' || buf[buf.size() - 1] == 'A')
            tatNum++;
    }
    if (leftNum == tatNum)
        leftNum--;
    if (rightNum == tatNum)
        rightNum--;

    cout << ans + max(0, min(leftNum, rightNum)) << '\n';

    return 0;
}
