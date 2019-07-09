#include <bits/stdc++.h>
using namespace std;

#define SIZE 210

int arr[SIZE], ans[SIZE];
pair<int, int> pos[SIZE];
vector<int> vec[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len;
    while (cin >> len) {
        if (len == 0)
            break;

        for (int i = 0; i < len; i++) {
            cin >> arr[i];
            arr[i]--; pos[i] = make_pair(-1, -1);
        }

        int permuNum = 0;
        for (int i = 0; i < len; i++) {
            if (pos[i].first != -1)
                continue;
            vec[permuNum].clear(); int cntPos = i;
            while (pos[cntPos].first == -1) {
                pos[cntPos] = make_pair(permuNum, vec[permuNum].size());
                vec[permuNum].push_back(cntPos);
                cntPos = arr[cntPos];
            }
            permuNum++;
        }

        int transNum;  string str;
        while (cin >> transNum) {
            if (transNum == 0)
                break;
            cin.ignore(); getline(cin, str);
            while ((int)str.size() < len)
                str.push_back(' ');

            for (int i = 0; i < len; i++) {
                int pt = vec[pos[i].first][(pos[i].second + transNum) % vec[pos[i].first].size()];
                ans[pt] = i;
            }
            for (int i = 0; i < len; i++)
                cout << str[ans[i]];
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}