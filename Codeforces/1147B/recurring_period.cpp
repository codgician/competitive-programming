#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

vector<int> vec[SIZE], pFac;
int len, segNum;

int primeArr[SIZE], minFacArr[SIZE], primePt;
void initPrime(int initSize) {
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    for (int i = 2; i <= initSize; i++) {
        if (minFacArr[i] == 0) {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], initSize / i); j++) {
            minFacArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

int getMinDis(int fstPt, int sndPt) {
    return min((fstPt - sndPt + len) % len, (sndPt - fstPt + len) % len);
}

void primeFac(int num) {
    for (int i = 0; i < primePt && primeArr[i] * primeArr[i] <= num; i++) {
        if (num % primeArr[i] != 0)
            continue;
        pFac.push_back(primeArr[i]);
        while (num % primeArr[i] == 0)
            num /= primeArr[i];
    }
    if (num > 1)
        pFac.push_back(num);
}

bool isEqual(int fstPt, int sndPt) {
    if (vec[fstPt].size() != vec[sndPt].size())
        return false;
    int len = vec[fstPt].size();
    for (int i = 0; i < len; i++)
        if (vec[fstPt][i] != vec[sndPt][i])
            return false;
    return true;
}

bool check(int cycNum) {
    int cycLen = len / cycNum;
    for (int i = cycLen; i < len; i++)
        if (!isEqual(i, i % cycLen))
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    initPrime(sqrt(SIZE) + 1);
    cin >> len >> segNum;
    for (int i = 0; i < segNum; i++) {
        int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        leftPt--; rightPt--;
        vec[leftPt].push_back(getMinDis(leftPt, rightPt));
        vec[rightPt].push_back(getMinDis(leftPt, rightPt));
    }

    for (int i = 0; i < len; i++)
        if (vec[i].size())
            sort(vec[i].begin(), vec[i].end());

    primeFac(len);
    for (auto i : pFac) {
        if (check(i)) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}