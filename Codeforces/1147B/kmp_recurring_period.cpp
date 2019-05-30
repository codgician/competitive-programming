#include <bits/stdc++.h>
using namespace std;

#define SIZE 200020

vector<int> vec[SIZE];
int len, segNum, nextArr[SIZE];

bool isEqual(int fstPt, int sndPt) {
    if (vec[fstPt].size() != vec[sndPt].size())
        return false;
    int len = vec[fstPt].size();
    for (int i = 0; i < len; i++)
        if (vec[fstPt][i] != vec[sndPt][i])
            return false;
    return true;
}

void initNext() {
    nextArr[0] = 0;
    for (int fstPt = 1, sndPt = 0; fstPt < len; fstPt++) {
        while (sndPt > 0 && !isEqual(fstPt, sndPt))
            sndPt = nextArr[sndPt - 1];
        if (isEqual(fstPt, sndPt))
            sndPt++;
        nextArr[fstPt] = sndPt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> len >> segNum;
    for (int i = 0; i < segNum; i++) {
        int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        leftPt--; rightPt--;
        if (leftPt > rightPt)
            swap(leftPt, rightPt);
        vec[leftPt].push_back((rightPt - leftPt + len) % len);
        vec[rightPt].push_back((leftPt - rightPt + len) % len);
    }

    for (int i = 0; i < len; i++)
        if (vec[i].size() > 1)
            sort(vec[i].begin(), vec[i].end());

    initNext();
    int cycLen = len - nextArr[len - 1];
    cout << ((cycLen < len && len % cycLen == 0) ? "Yes\n" : "No\n");

    return 0;
}