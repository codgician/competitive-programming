#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode {
    int leftPt, rightPt;
    pair<int, int> minv; int lazy;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt) {
    segTree[segPt].minv = min(segTree[LEFT_SON].minv, segTree[RIGHT_SON].minv);
}

void pushDown(int segPt) {
    if (segTree[segPt].lazy == 0)
        return;

    segTree[LEFT_SON].minv.first += segTree[segPt].lazy;
    segTree[RIGHT_SON].minv.first += segTree[segPt].lazy;

    segTree[LEFT_SON].lazy += segTree[segPt].lazy;
    segTree[RIGHT_SON].lazy += segTree[segPt].lazy;

    segTree[segPt].lazy = 0;
}

void build(int segPt, int leftPt, int rightPt) {
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    segTree[segPt].lazy = 0;
    if (leftPt == rightPt) {
        segTree[segPt].minv = make_pair(0, leftPt);
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
}

void rangeAdd(int segPt, int qLeftPt, int qRightPt, int val) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt) {
        segTree[segPt].minv.first += val;
        segTree[segPt].lazy += val;
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeAdd(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeAdd(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

pair<int, int> rangeQuery(int segPt, int qLeftPt, int qRightPt) {
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
        return segTree[segPt].minv;
    
    pushDown(segPt); pair<int, int> ret = make_pair(INT_MAX, INT_MAX);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        ret = min(ret, rangeQuery(LEFT_SON, qLeftPt, qRightPt));
    if (qRightPt > midPt)
        ret = min(ret, rangeQuery(RIGHT_SON, qLeftPt, qRightPt));
    return ret;
}

int arr[SIZE], pre[SIZE], prek[SIZE];
int len, maxv, k;
pair<int, int> prevRange[SIZE];
vector<int> vec[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while (cin >> len >> maxv >> k) {
        for (int i = 0; i <= maxv; i++) {
            vec[i].clear(); pre[i] = 0; prek[i] = 0;
            prevRange[i] = make_pair(1, 0);
        }

        build(1, 1, len); int ans = 0;
        for (int i = 1; i <= len; i++) {
            int cnt; cin >> cnt;
            vec[cnt].push_back(i);

            pre[cnt] = i;
            if ((int)vec[cnt].size() >= k)
                prek[cnt] = vec[cnt][vec[cnt].size() - k];

            int leftPt = prek[cnt] + 1, rightPt = pre[cnt];
            if (leftPt <= rightPt) {
                // Revert
                if (prevRange[cnt].first <= prevRange[cnt].second)
                    rangeAdd(1, prevRange[cnt].first, prevRange[cnt].second, -1);
                // Update
                rangeAdd(1, leftPt, rightPt, 1);
                prevRange[cnt] = make_pair(leftPt, rightPt);
            }

            pair<int, int> ret = rangeQuery(1, 1, i);
            if (ret.first == 0)
                ans = max(ans, i - ret.second + 1);
        }

        cout << ans << '\n';
    }

    return 0;
}