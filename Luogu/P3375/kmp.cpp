#include <bits/stdc++.h>
#define SIZE 1000100
using namespace std;

int nextArr[SIZE];
vector<int> vec;

void initNext(const string & str) {
    nextArr[0] = 0; int len = str.size();
    for (int fstPt = 1, sndPt = 0; fstPt < len; fstPt++) {
        while (sndPt > 0 && str[fstPt] != str[sndPt])
            sndPt = nextArr[sndPt - 1];
        if (str[fstPt] == str[sndPt])
            sndPt++;
        nextArr[fstPt] = sndPt;
    }
}

int kmp(const string & fst, const string & snd) {
    int fstLen = fst.size(), sndLen = snd.size(), ret = 0;
    for (int fstPt = 0, sndPt = 0; fstPt < fstLen; fstPt++) {
        while (sndPt > 0 && (sndPt == sndLen || fst[fstPt] != snd[sndPt]))
            sndPt = nextArr[sndPt - 1];
        if (fst[fstPt] == snd[sndPt])
            sndPt++;
        if (sndPt == sndLen) {
            vec.push_back(fstPt - sndPt + 1);
            ret++;
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string fst, snd;
    cin >> fst >> snd;
    initNext(snd);

    kmp(fst, snd);
    for (auto i : vec)
        cout << i + 1 << '\n';
    cout << nextArr[0];
    for (int i = 1; i < (int)snd.size(); i++)
        cout << " " << nextArr[i];
    cout << '\n';
    return 0;
}
