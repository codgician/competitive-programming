#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010
#define LEFT_SON (rt << 1)
#define RIGHT_SON (rt << 1 | 1)

class SegNode {
public:
    int leftPt, rightPt;
    int minv, maxv, lazy;
};

SegNode segt[SIZE << 2];

void pushUp(int rt) {
    segt[rt].minv = min(segt[LEFT_SON].minv, segt[RIGHT_SON].minv);
    segt[rt].maxv = max(segt[LEFT_SON].maxv, segt[RIGHT_SON].maxv);
}

void pushDown(int rt) {
    if (segt[rt].lazy == 0)
        return;

    segt[LEFT_SON].minv += segt[rt].lazy;
    segt[RIGHT_SON].minv += segt[rt].lazy;
    segt[LEFT_SON].maxv += segt[rt].lazy;
    segt[RIGHT_SON].maxv += segt[rt].lazy;
    segt[LEFT_SON].lazy += segt[rt].lazy;
    segt[RIGHT_SON].lazy += segt[rt].lazy;
    segt[rt].lazy = 0;
}

void build(int rt, int leftPt, int rightPt) {
    segt[rt].leftPt = leftPt;
    segt[rt].rightPt = rightPt;
    segt[rt].lazy = 0;
    if (leftPt == rightPt) {
        segt[rt].maxv = 0;
        segt[rt].minv = 0;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(rt);
}

void addRange(int rt, int qLeftPt, int qRightPt, int val) {
    if (segt[rt].leftPt >= qLeftPt && segt[rt].rightPt <= qRightPt) {
        segt[rt].maxv += val; segt[rt].minv += val;
        segt[rt].lazy += val;
        return;
    }
    pushDown(rt);
    int midPt = (segt[rt].leftPt + segt[rt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        addRange(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        addRange(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(rt);
}

int queryMin(int rt, int qLeftPt, int qRightPt) {
    if (segt[rt].leftPt >= qLeftPt && segt[rt].rightPt <= qRightPt) {
        return segt[rt].minv;
    }
    pushDown(rt);
    int ans = INT_MAX, midPt = (segt[rt].leftPt + segt[rt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = min(ans, queryMin(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = min(ans, queryMin(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

int queryMax(int rt, int qLeftPt, int qRightPt) {
    if (segt[rt].leftPt >= qLeftPt && segt[rt].rightPt <= qRightPt) {
        return segt[rt].maxv;
    }
    pushDown(rt);
    int ans = INT_MIN, midPt = (segt[rt].leftPt + segt[rt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ans = max(ans, queryMax(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ans = max(ans, queryMax(RIGHT_SON, qLeftPt, qRightPt));
    return ans;
}

int queryPos(int pos) {
    int ret = queryMax(1, pos, pos);
    if (pos > 1)
        ret -= queryMax(1, pos - 1, pos - 1);
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int qNum; string ques; cin >> qNum >> ques;
    build(1, 1, qNum);

    int cntPos = 1;
    for (const auto & q : ques) {
        if (q == 'L') {
            cntPos = max(1, cntPos - 1);
        } else if (q == 'R') {
            cntPos++;
        } else if (q == '(') {
            int cnt = queryPos(cntPos);
            if (cnt == -1) {
                addRange(1, cntPos, qNum, 2);
            } else if (cnt == 0) {
                addRange(1, cntPos, qNum, 1);
            }
        } else if (q == ')') {
            int cnt = queryPos(cntPos);
            if (cnt == 1) {
                addRange(1, cntPos, qNum, -2);
            } else if (cnt == 0) {
                addRange(1, cntPos, qNum, -1);
            }
        } else {
            int cnt = queryPos(cntPos);
            if (cnt == 1) {
                addRange(1, cntPos, qNum, -1);
            } else if (cnt == -1) {
                addRange(1, cntPos, qNum, 1);
            }
        }

        const auto check = [qNum]() {
            return queryMax(1, qNum, qNum) == 0 && queryMin(1, 1, qNum) >= 0;
        };
        cout << (check() ? queryMax(1, 1, qNum) : -1) << ' ';
    }
    
    return 0;
}