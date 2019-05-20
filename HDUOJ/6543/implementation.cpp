#include <bits/stdc++.h>
using namespace std;

string fst, snd;
int arr[26];

bool check() {
    int fstLen = fst.size(), sndLen = snd.size();
    if (fstLen != sndLen || fst[0] != snd[0] || fst[fstLen - 1] != snd[sndLen - 1])
        return false;
    memset(arr, 0, sizeof(arr));
    for (int i = 1; i < fstLen - 1; i++)
        arr[fst[i] - 'a']++;
    for (int i = 1; i < sndLen - 1; i++)
        arr[snd[i] - 'a']--;
    for (int i = 0; i < 26; i++)
        if (arr[i] != 0)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (cin >> fst >> snd) {
        if (fst == snd)
            cout << "Equal\n";
        else
            cout << (check() ? "Yes\n" : "No\n");
    }
    return 0;
}