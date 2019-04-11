#include <bits/stdc++.h>
using namespace std;

#define SIZE 210

map<string, int> mp;
string strArr[SIZE];
bitset<SIZE> arr[SIZE], qArr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int num, qNum, known;
        cin >> num >> qNum >> known;
        mp.clear();

        for (int i = 0; i < num; i++) {
            arr[i].reset();
            for (int j = 0; j < known; j++) {
                arr[i].set(j, 1);
            }
        }

        for (int i = 0; i < known; i++) {
            cin >> strArr[i];
            mp[strArr[i]] = i;
        }

        for (int i = 0; i < qNum; i++) {
            qArr[i].reset();
            int cntNum;
            cin >> cntNum;
            while (cntNum--) {
                string str;
                cin >> str;
                qArr[i].set(mp[str], 1);
            }
        }

        for (int i = 0; i < num; i++) {
            for (int j = 0; j < qNum; j++) {
                int cnt;
                cin >> cnt;
                if (cnt == 1) {
                    arr[i] &= qArr[j];
                } else {
                    for (int k = 0; k < known; k++) {
                        if (arr[i][k] == 1 && qArr[j][k] == 0) {
                            arr[i][k] = 1;
                        } else {
                            arr[i][k] = 0;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < num; i++) {
            if (arr[i].count() != 1) {
                cout << "Let's go to the library!!" << endl;
            } else {
                int pt = -1;
                for (int j = 0; j < known; j++) {
                    if (arr[i][j] == 1) {
                        pt = j;
                        break;
                    }
                }
                cout << strArr[pt] << endl;
            }
        }
    }

    return 0;
}