#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 110
 
char arr[SIZE][SIZE], ret[SIZE][SIZE];
vector<int> chs;
 
void init() {
    chs.clear();
    for (int i = 0; i < 26; i++)
        chs.push_back('A' + i), chs.push_back('a' + i);
    for (int i = 0; i < 10; i++)
        chs.push_back('0' + i);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    init(); int caseNum; cin >> caseNum;
    while (caseNum--) {
        int row, col, chick, rice = 0;
        cin >> row >> col >> chick;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                cin >> arr[i][j], rice += (arr[i][j] == 'R');
        
        int avg = rice / chick, md = rice % chick, cnt = 0, chid = 0; 
        for (int i = 0; i < row; i++) {
            int startPt = (i & 1) ? col - 1 : 0;
            int endPt = (i & 1) ? -1 : col, inc = (i & 1) ? -1 : 1;
            for (int j = startPt; j != endPt; j += inc) {
                cnt += arr[i][j] == 'R'; ret[i][j] = chs[chid];
                if (md > 0 && cnt == avg + 1) {
                    chid++; cnt = 0; md--;
                } else if (md == 0 && cnt == avg && chid < chick - 1) {
                    chid++; cnt = 0;
                }
            }
        }
 
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++)
                cout << ret[i][j];
            cout << '\n';
        }
    }
 
    return 0;
}