#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 100010
#define BIT_SIZE 320

class Query {
public:
    int id, x, y, z;
    bool operator < (const Query & snd) const {
        if (x != snd.x)
            return x < snd.x;
        if (y != snd.y)
            return y < snd.y;
        if (z != snd.z)
            return z < snd.z;
        return id < snd.id;
    }
};
 
Query qArr[SIZE], bkup[SIZE];
int ans[SIZE], bit[BIT_SIZE][BIT_SIZE];
int xLim, yLim, zLim, qPt, idPt;
 
int lowbit(int n) {
    return n & -n;
}
 
void addMax(int x, int y, int val) {
    for (int i = x; i <= yLim + 2; i += lowbit(i))
        for (int j = y; j <= zLim + 2; j += lowbit(j))
            bit[i][j] = max(bit[i][j], val);
}
 
int prefixMax(int x, int y) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            ret = max(ret, bit[i][j]);
    return ret;
}
 
void clear(int x, int y) {
    for (int i = x; i <= yLim + 2; i += lowbit(i))
        for (int j = y; j <= zLim + 2; j += lowbit(j))
            bit[i][j] = 0;
}
 
void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);
 
    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (qArr[i].id == -1)
            continue;
        for (; j <= midPt && qArr[j].x <= qArr[i].x; j++)
            if (qArr[j].id == -1)
                addMax(qArr[j].y, qArr[j].z, qArr[j].x + qArr[j].y + qArr[j].z);
        int ret = prefixMax(qArr[i].y, qArr[i].z);
        if (ret != 0)
            ans[qArr[i].id] = min(ans[qArr[i].id], qArr[i].x + qArr[i].y + qArr[i].z - ret);
    }
 
    for (int i = headPt; i < j; i++)
        if (qArr[i].id == -1)
            clear(qArr[i].y, qArr[i].z);
 
    inplace_merge(qArr + headPt, qArr + midPt + 1, qArr + tailPt + 1);
}
 
void trans(int st) {
    for (int i = 0; i < qPt; i++) {
        qArr[i] = bkup[i];
        if (st & 1)
            qArr[i].x = xLim + 1 - qArr[i].x;
        if ((st >> 1) & 1)
            qArr[i].y = yLim + 1 - qArr[i].y;
        if ((st >> 2) & 1)
            qArr[i].z = zLim + 1 - qArr[i].z;       
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int qNum; cin >> xLim >> yLim >> zLim >> qNum;
    qPt = 0, idPt = 0;
    for (int i = 0; i < qNum; i++) {
        int op; cin >> op >> qArr[qPt].x >> qArr[qPt].y >> qArr[qPt].z;
        qArr[qPt++].id = (op == 1 ? -1 : idPt++);
    }
     
    int maxv = max({xLim, yLim, zLim});
    if (yLim == maxv) {
        swap(xLim, yLim);
        for (int i = 0; i < qPt; i++)
            swap(qArr[i].x, qArr[i].y);
    } else if (zLim == maxv) {
        swap(xLim, zLim);
        for (int i = 0; i < qPt; i++)
            swap(qArr[i].x, qArr[i].z);
    }
    
    for (int i = 0; i <= yLim + 2; i++)
        for (int j = 0; j <= zLim + 2; j++)
            bit[i][j] = 0;
    fill(ans + 0, ans + idPt, INT_MAX);
    copy(qArr + 0, qArr + qPt, bkup + 0);
 
    for (int i = 0; i < 8; i++) {
        trans(i);
        divideConquer(0, qPt - 1);
    }
 
    for (int i = 0; i < idPt; i++)
        cout << ans[i] << '\n';
  
    return 0;
}