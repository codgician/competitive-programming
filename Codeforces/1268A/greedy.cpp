#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, k; string str, sub, ret;
    cin >> n >> k >> str;
    for (int i = 0; i < k; i++)
        sub.push_back(str[i]);
    for (int i = 0; i < n / k; i++)
        ret += sub;
    int cntPt = 0;
    while (ret.size() < str.size())
        ret.push_back(sub[cntPt++]);

    if (ret < str) {
        int cntPt = k - 1;
        while (cntPt >= 0 && str[cntPt] == '9')
            cntPt--;
        for (int i = cntPt; i < n; i += k)
            ret[i]++;
        for (int i = cntPt + 1; i < k; i++)
            for (int j = i; j < n; j += k)
                ret[j] = '0';
    }

    cout << ret.size() << '\n';
    cout << ret << '\n';

    return 0;
}