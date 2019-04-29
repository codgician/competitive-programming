#include <bits/stdc++.h>
using namespace std;

#define SIZE 11000010

int radius[SIZE << 1];
string man;

void init(const string & str) {
    memset(radius, 0, sizeof(radius));
    man.clear();
    man.push_back('#');
    for (auto ch : str) {
        man.push_back(ch);
        man.push_back('#');
    }
}

void manacher() {
    int rightPt = -1, midPt = -1, len = man.size();
    for (int i = 0; i < len; i++) {
        radius[i] = i < rightPt ? min(radius[(midPt << 1) - i], radius[midPt] + midPt - i) : 1;
        while (radius[i] < min(len - i, i + 1) && man[i + radius[i]] == man[i - radius[i]])
            radius[i]++;
        if (radius[i] + i > rightPt) {
            rightPt = radius[i] + i;
            midPt = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string str;
    cin >> str;
    init(str);
    manacher();

    int ans = 0;
    for (int i = 0; i < (int)man.size(); i++)
        ans = max(ans, radius[i]);
    cout << ans - 1 << '\n';

    return 0;
}