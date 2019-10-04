#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    string a, b, last, ans; queue<char> q;
    int keyLen, textLen; cin >> keyLen >> textLen;
    cin >> last >> b;

    for (int i = (int)last.size() - 1; i >= 0; i--)
        q.push(last[i]), ans.push_back(last[i]);

    while (!q.empty() && !b.empty()) {
        char ch = 'a' + (b.back() - q.front() + 26) % 26; q.pop();
        b.pop_back(); q.push(ch); ans.push_back(ch);
    }

    while (keyLen--)
        ans.pop_back();
    reverse(ans.begin(), ans.end()); cout << ans << '\n';
    return 0;
}