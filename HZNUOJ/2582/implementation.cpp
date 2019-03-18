#include <bits/stdc++.h>
using namespace std;

vector<int> vec;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num, ans;
    cin >> num;
    ans = num;
    for (int i = 0; i < num; i++) {
        int cnt;
        cin >> cnt;
        vec.push_back(cnt);
    }
    sort(vec.begin(),vec.end());

    for (int i = 1; i < num; i++)
        if (vec[i] == vec[i - 1])
            ans--;
    cout << ans << endl;
    return 0;
}