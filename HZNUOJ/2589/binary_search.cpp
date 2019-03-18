#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define DOT_SIZE 260
#define AREA_SIZE 2573100

int dot[DOT_SIZE][2];
long long int siz[AREA_SIZE];   // siz * 2

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num, qNum;
    cin >> num >> qNum;
    for (int i = 0; i < num; i++) {
        cin >> dot[i][0] >> dot[i][1];
    }

    int sizPt = 0;
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            for (int k = j + 1; k < num; k++) {
                long long int x1 = dot[j][0] - dot[i][0], y1 = dot[j][1] - dot[i][1];
                long long int x2 = dot[j][0] - dot[k][0], y2 = dot[j][1] - dot[k][1];
                long long int cnt = abs(x1 * y2 - x2 * y1);
                siz[sizPt++] = cnt;
            }
        }
    }

    sort(siz + 0, siz + sizPt);
    
    while (qNum--) {
        long long int qLeftPt, qRightPt;
        cin >> qLeftPt >> qRightPt;
        qLeftPt <<= 1;
        qRightPt <<= 1;
        
        int leftRnk = lower_bound(siz + 0, siz + sizPt, qLeftPt) - siz;
        int rightRnk = upper_bound(siz + 0, siz + sizPt, qRightPt) - siz;
        long long int ans = rightRnk - leftRnk;
        cout << ans << endl;
    }
    
    return 0;
}