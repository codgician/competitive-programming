#include <bits/stdc++.h>
using namespace std;

#define SIZE 2000010

int radius[SIZE << 1];
string man, fst, snd;

void init() {
    man.clear();
    man.push_back('#');
    for (auto ch : fst) {
        man.push_back(ch);
        man.push_back('#');
    }
}

void manacher() {
    int rightPt = -1, midPt = -1, len = man.size();
    for (int i = 0; i < len; i++)
        radius[i] = 0;
    for (int i = 0; i < len; i++) {
        radius[i] = i < rightPt ? min(radius[(midPt << 1) - i], radius[midPt] + midPt - i) : 1;
        while (radius[i] < min(len - i, i + 1) && man[i + radius[i]] == man[i - radius[i]])
            radius[i]++;
        if (radius[i] + i > rightPt) {
            rightPt = radius[i] + i;
            midPt = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        cin >> fst >> snd;
        if (fst.size() != snd.size()) {
            cout << "0\n";
            continue;
        }
        int len = fst.size();
        int leftPt = INT_MAX, rightPt = -1;
        for (int i = 0; i < len; i++) {
            if (fst[i] != snd[i]) {
                leftPt = min(leftPt, i);
                rightPt = max(rightPt, i);
            }
        }

        long long int ans = 0;
        if (rightPt == -1) {
            // Identical strings
            init();
            manacher();
            for (int i = 0; i < (int)man.size(); i++)
                if (radius[i] > 0)
                    ans += radius[i] >> 1;
        } else {
            int fstPt = leftPt, sndPt = rightPt;
            bool canReverse = true;
            while (fstPt <= rightPt && sndPt >= leftPt && canReverse) {
                if (fst[fstPt] != snd[sndPt])
                    canReverse = false;
                fstPt++; sndPt--;
            }

            if (!canReverse) {
                cout << "0\n";
                continue;
            }

            fstPt = leftPt, sndPt = rightPt;
            while (fstPt >= 0 && sndPt < len) {
                if (fst[fstPt] != snd[sndPt])
                    break;
                ans++;
                fstPt--; sndPt++;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}