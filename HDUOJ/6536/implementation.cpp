#include <bits/stdc++.h>
using namespace std;

#define SIZE 10

int num[SIZE], len;
string str;

int getId(char ch) {
    if (ch == 'x')
        return 0;
    if (ch == 't')
        return 1;
    if (ch == 'C')
        return 2;
    if (ch == 'p')
        return 3;
    if (ch == 'c')
        return 4;
    return 5;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len; 
    while (cin >> len >> str) {
        memset(num, 0, sizeof(num));
        for (int i = 0; i < len; i++) {
            int cntId = getId(str[i]);
            if (cntId == 5)
                continue;
            if (cntId == 0 || num[cntId - 1] > num[cntId])
                num[cntId]++;
        }
        cout << num[4] << '\n';
    }

    return 0;
}