#include <iostream>
#include <string>
using namespace std;

#define SIZE 30

bool vis[SIZE];
int num[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        fill(vis + 0, vis + SIZE, false);
        fill(num + 0, num + SIZE, 0);
        string str; cin >> str;
        int len = str.size();

        for (int i = 0; i < len; i++) {
            if (vis[i])
                continue;

            int cntPos = i, cntSiz = 0;
            while (!vis[cntPos]) {
                vis[cntPos] = true; cntSiz++;
                cntPos = str[cntPos] - 'A';
            }
            num[cntSiz]++;
        }      

        bool ans = true;
        for (int i = 2; i <= 26 && ans; i += 2)
            if (num[i] & 1)
                ans = false;
        cout << (ans ? "Yes\n" : "No\n");
    }
    return 0;
}