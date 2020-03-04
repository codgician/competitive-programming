#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010
#define VAL_SIZE 1000010

class Monster {
public:
    int x, y, z;
    bool operator < (const Monster & snd) {
        if (x != snd.x)
            return x < snd.x;
        if (y != snd.y)
            return y < snd.y;
        return z < snd.z;
    }
};

Monster mons[SIZE];
pair<int, int> wea[SIZE], arm[SIZE];
int pfx[VAL_SIZE];

class SegTree {
public:
    int leftPt, rightPt;
    int maxv, lazy;
};

SegTree segt[VAL_SIZE << 2];

#define LEFT_SON (rt << 1)
#define RIGHT_SON (rt << 1 | 1)

void pushUp(int rt) {
    segt[rt].maxv = max(segt[LEFT_SON].maxv, segt[RIGHT_SON].maxv);
}

void pushDown(int rt) {
    int inc = segt[rt].lazy;
    if (inc == 0)
        return;
    segt[LEFT_SON].maxv += inc, segt[LEFT_SON].lazy += inc;
    segt[RIGHT_SON].maxv += inc, segt[RIGHT_SON].lazy += inc;
    segt[rt].lazy = 0;
}

void build(int rt, int leftPt, int rightPt) {
    segt[rt] = {leftPt, rightPt, INT_MIN, 0};
    if (leftPt == rightPt) {
        segt[rt].maxv = -pfx[leftPt];
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(rt);
}

void rangeAdd(int rt, int qLeftPt, int qRightPt, int val) {
    assert(qLeftPt <= qRightPt);
    if (segt[rt].leftPt >= qLeftPt && segt[rt].rightPt <= qRightPt) {
        segt[rt].maxv += val, segt[rt].lazy += val;
        return;
    }
    
    pushDown(rt); int midPt = (segt[rt].leftPt + segt[rt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeAdd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeAdd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(rt);
}

int rangeMax(int rt, int qLeftPt, int qRightPt) {
    assert(qLeftPt <= qRightPt);
    if (segt[rt].leftPt >= qLeftPt && segt[rt].rightPt <= qRightPt) {
        return segt[rt].maxv;
    }

    int ret = INT_MIN; pushDown(rt); 
    int midPt = (segt[rt].leftPt + segt[rt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ret = max(ret, rangeMax(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ret = max(ret, rangeMax(RIGHT_SON, qLeftPt, qRightPt));
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int weaNum, armNum, monsNum, maxa = 0;
    cin >> weaNum >> armNum >> monsNum;

    for (int i = 0; i < weaNum; i++)
        cin >> wea[i].first >> wea[i].second;
    for (int i = 0; i < armNum; i++)
        cin >> arm[i].first >> arm[i].second, maxa = max(maxa, arm[i].first);
    for (int i = 0; i < monsNum; i++)
        cin >> mons[i].x >> mons[i].y >> mons[i].z;
    sort(wea + 0, wea + weaNum);
    sort(arm + 0, arm + armNum);
    sort(mons + 0, mons + monsNum);

    fill(pfx + 0, pfx + maxa + 1, INT_MAX);
    for (int i = 0; i < armNum; i++)
        pfx[arm[i].first] = min(pfx[arm[i].first], arm[i].second);
    for (int i = maxa - 1; i >= 1; i--)
        pfx[i] = min(pfx[i + 1], pfx[i]);
    build(1, 1, maxa);

    int ans = INT_MIN;
    for (int i = 0, j = 0; i < weaNum; i++) {
        for (; j < monsNum && wea[i].first > mons[j].x; j++)
            if (mons[j].y + 1 <= maxa)
                rangeAdd(1, mons[j].y + 1, maxa, mons[j].z);
        ans = max(ans, rangeMax(1, 1, maxa) - wea[i].second);
    }
    cout << ans << '\n';
    return 0;
}