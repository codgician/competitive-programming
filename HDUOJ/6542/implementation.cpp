#include <bits/stdc++.h>
using namespace std;

#define SIZE 40

int num[SIZE];

int getId(string str) {
    if (str[0] >= '1' && str[0] <= '9') {
        // number card: [0, 26]
        if (str[1] == 's')
            return str[0] - '1';
        if (str[1] == 'p')
            return 1 * 9 + (str[0] - '1');
        if (str[1] == 'w')
            return 2 * 9 + (str[0] - '1');
    }

    // word card: [27, 33]
    if (str[0] == 'd')
        return 27;
    if (str[0] == 'n')
        return 28;
    if (str[0] == 'x')
        return 29;
    if (str[0] == 'b' && str[1] == 'e')
        return 30;
    if (str[0] == 'z')
        return 31;
    if (str[0] == 'f')
        return 32;
    return 33;
}

bool checkFst() {
    for (int i = 0; i < 3; i++)
        if (num[9 * i + 0] == 0 || num[9 * i + 8] == 0)
            return false;
    for (int i = 27; i < 34; i++)
        if (num[i] == 0)
            return false;
    for (int i = 0; i < 3; i++)
        for (int j = 1; j < 8; j++)
            if (num[9 * i + j] > 0)
                return false;
    return true;
}

bool checkSnd() {
    for (int j = 0; j < 9; j++)
        if ((int)(num[j] > 0) + (num[9 + j] > 0) + (num[18 + j] > 0) > 1)
            return false;
    if (num[0] + num[9] + num[18] < 3)
        return false;
    if (num[8] + num[9 + 8] + num[18 + 8] < 3)
        return false;
    for (int j = 1; j < 8; j++) {
        int cntNum = 0;
        for (int i = 0; i < 3; i++)
            cntNum += num[9 * i + j];
        if (cntNum < 1)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string str;
    while (cin >> str) {
        memset(num, 0, sizeof(num));
        num[getId(str)]++;
        for (int i = 1; i < 14; i++) {
            cin >> str;
            num[getId(str)]++;
        }

        if (checkFst()) {
            cout << "shisanyao!\n";
            continue;
        }

        if (checkSnd()) {
            cout << "jiulianbaodeng!\n";
            continue;
        }

        cout << "I don't know!\n";
    }

    return 0;
}