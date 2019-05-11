#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long int redNum, greenNum, blueNum, tot;
    cin >> redNum >> greenNum >> blueNum >> tot;

    long long int ans = 0;
    for (int i = 0; i * redNum <= tot; i++)
        for (int j = 0; i * redNum + j * greenNum <= tot; j++)
            if ((tot - (i * redNum + j * greenNum)) % blueNum == 0)
                ans++;
    cout << ans << '\n';

    return 0;
}
