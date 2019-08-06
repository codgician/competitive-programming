#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 8
 
int arr[SIZE];
 
char conv(int num) {
    if (num < 10)
        return '0' + num;
    return 'a' - 10 + num;
}
 
string dec2Hex(int num) {
    string ret;
    if (num == 0)
        return "0";
    while (num > 0) {
        ret.push_back(conv(num % 16));
        num >>= 4;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        fill(arr + 0, arr + SIZE, 0);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 16; j++) {
                char ch; cin >> ch;
                arr[i] = (arr[i] << 1) + (ch - '0');
            }
        }
 
        /*
        for (int i = 0; i < 8; i++)
            cerr << arr[i] << " ";
        cerr << endl;
        */
 
        // Find most consecutive 0
        int maxLen = -1, fstMaxPt = -1, sndMaxPt = -1;
        for (int i = 0; i < 8; i++) {
            if (arr[i] != 0)
                continue;
            int pt = 0;
            while (i + pt < 8 && arr[i + pt] == 0)
                pt++;
            if (pt > maxLen)
                maxLen = pt, fstMaxPt = i, sndMaxPt = -1;
            else if (pt == maxLen && sndMaxPt == -1)
                sndMaxPt = fstMaxPt, fstMaxPt = i;
        }
 
        if (maxLen == 1)
            maxLen = -1, fstMaxPt = -1, sndMaxPt = -1;
 
        if (fstMaxPt + maxLen == 8 && sndMaxPt != -1 && sndMaxPt != 0)
            fstMaxPt = sndMaxPt;
 
        cout << "Case #" << t << ": ";
        for (int i = 0; i < 8; i++) {
            if (i == fstMaxPt) {
                cout << "::";
                i = i + maxLen - 1;
                continue;
            }
 
            cout << dec2Hex(arr[i]);
            if (i + 1 != fstMaxPt && i < 7)
                cout << ":";
        }
        cout << '\n';
    }
 
    return 0;
}