#include <bits/stdc++.h>
using namespace std;

int nums[4], cnt[4];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    for (int t = 0; t < 4; t++)
        cin >> nums[t];

    // Enumerate first element
    for (int t = 0; t < 4; t++) {
        if (nums[t] == 0)
            continue;
        vector<int> vec; int val = t;
        copy(nums + 0, nums + 4, cnt + 0);
        while (true) {
            vec.push_back(val); cnt[val]--;
            if (val > 0 && cnt[val - 1] > 0) {
                val = val - 1;
            } else if (val < 3 && cnt[val + 1] > 0) {
                val = val + 1;
            } else {
                break;
            }
        }

        if (max({cnt[0], cnt[1], cnt[2], cnt[3]}) == 0) {
            cout << "YES\n";
            for (const auto & i : vec)
                cout << i << ' ';
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}
