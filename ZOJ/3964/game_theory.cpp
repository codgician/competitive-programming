#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int num;
        cin >> num;
        for (int i = 0; i < num; i++)
            cin >> arr[i];
        int xorSum = 0, evenNum = 0, oddNum = 0;
        bool ans = true;
        for (int i = 0; i < num; i++) {
            int typ;
            cin >> typ;
            if (typ == 1) {
                if (arr[i] > 1) {
                    oddNum++;
                    arr[i] = (arr[i] + 1) & 1;
                }
            } else if (typ == 2) {
                evenNum++;
                if (arr[i] & 1)
                    ans = false;
                arr[i] = 0;
            }
            xorSum ^= arr[i];
        }

        if (oddNum + evenNum > 1)
            ans = false;

        if (!ans) {
            cout << "Bob\n";
            continue;
        }

        if (evenNum == 0 && oddNum == 0) {
            cout << (xorSum == 0 ? "Bob\n" : "Alice\n");
        } else {
            cout << (xorSum == 0 ? "Alice\n" : "Bob\n");
        }
    }

    return 0;
}