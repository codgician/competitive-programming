#include <bits/stdc++.h>
using namespace std;

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);



    return 0;
}