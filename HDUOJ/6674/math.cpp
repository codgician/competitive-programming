#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> mp; vector<int> vec;

int bitSum(int num) {
    int ret = 0;
    while (num > 0) {
        ret += num % 10;
        num /= 10;
    }
    return ret;
}

void factorize(int num) {
    for (int i = 1; i * i <= num; i++) {
        if (num % i != 0)
            continue;
        mp[i]++;
        if (i * i != num)
            mp[num / i]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        mp.clear(); vec.clear();
        int num; cin >> num;
        factorize(num); factorize(bitSum(num));
        for (const auto & p : mp)
            if (p.second == 2)
                vec.push_back(p.first);
        sort(vec.begin(), vec.end());
        int siz = vec.size();
        cout << siz << '\n';
        cout << vec[0];
        for (int i = 1; i < siz; i++)
            cout << ' ' << vec[i];
        cout << '\n';
    }

    return 0;
}