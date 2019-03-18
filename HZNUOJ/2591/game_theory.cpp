#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

int primeArr[SIZE], minFacArr[SIZE], primePt;
int arr[SIZE], sg[SIZE];

void initPrime() {
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    sg[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        if (minFacArr[i] == 0) {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
            sg[i] = primePt + 1;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++) {
            minFacArr[i * primeArr[j]] = primeArr[j];
            sg[i * primeArr[j]] = sg[primeArr[j]]; 
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrime();
    
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        int num, ans = 0;
        cin >> num;
        for (int i = 0; i < num; i++) {
            cin >> arr[i];
            ans ^= sg[arr[i]];
        }

        if (ans)
            cout << "Subconscious is our king!\n";
        else
            cout << "Long live with King Johann!\n";
    }

    return 0;
}