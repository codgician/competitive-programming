#include <bits/stdc++.h>
using namespace std;

string odd, even;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        odd.clear(); even.clear();
        string str;
        cin >> str;
        for (auto ch : str) {
            if ((ch - 'a') & 1)
                odd.push_back(ch);
            else
                even.push_back(ch);
        }
        sort(odd.begin(), odd.end());
        sort(even.begin(), even.end());

        if (even.empty() || odd.empty() || abs(odd.back() - even.front()) != 1)
            cout << odd << even << '\n';
        else if (abs(even.back() - odd.front()) != 1)
            cout << even << odd << '\n';
        else
            cout << "No answer\n";
    }

    return 0;
}