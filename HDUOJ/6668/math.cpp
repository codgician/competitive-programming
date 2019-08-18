#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

int fst[SIZE], snd[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int len; cin >> len;
        for (int i = 0; i < len; i++)
            cin >> fst[i];
        for (int i = 0; i < len; i++)
            cin >> snd[i];

        int fstPt = len - 1, sndPt = len - 1;
        while (fstPt > 0 && fst[fstPt] == 0)
            fstPt--;
        while (sndPt > 0 && snd[sndPt] == 0)
            sndPt--;

        if (fstPt > sndPt) {
            cout << "1/0\n";
        } else if (fstPt < sndPt) {
            cout << "0/1\n";
        } else {
            int a = fst[fstPt], b = snd[sndPt];
            int gcd = __gcd(a, b);
            a /= gcd; b /= gcd;
            cout << a << '/' << b << '\n';
        }
    }
    return 0;
}