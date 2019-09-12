#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

class Query {
public:
    int id, type, x, y, z;
    bool operator < (const Query & snd) const {
        if (x != snd.x)
            return x < snd.x;
        if (id != snd.id)
            return id < snd.id;
        if (y != snd.y)
            return y < snd.y;
        if (z != snd.z)
            return z < snd.z;
        return type < snd.type;
    }
};

Query ques[SIZE << 3];
int arr[SIZE], pre[SIZE], bit[SIZE], bound[SIZE], ans[SIZE];

int lowbit(int n) {
    return n & -n;
}

void add(int pos, int val) {
    pos++;
    for (int i = pos; i < SIZE; i += lowbit(i))
        bit[i] += val;
}

int prefixSum(int pos) {
    int ret = 0; pos++;
    for (int i = pos; i > 0; i -= lowbit(i))
        ret += bit[i];
    return ret;
}

int rangeSum(int qLeftPt, int qRightPt) {
    if (qRightPt < qLeftPt)
        return 0;
    return prefixSum(qRightPt) - prefixSum(qLeftPt - 1);
}

void divideConquer(int headPt, int tailPt) {
    if (headPt == tailPt)
        return;
    int midPt = (headPt + tailPt) >> 1;
    divideConquer(headPt, midPt);
    divideConquer(midPt + 1, tailPt);

    int j = headPt;
    for (int i = midPt + 1; i <= tailPt; i++) {
        if (ques[i].id == -1)
            continue;
        for (; j <= midPt && ques[j].x <= ques[i].x; j++) {
            if (ques[j].id == -1) {
                if (ques[j].y == ques[j].z)
                    add(ques[j].y, ques[j].type);
                bound[ques[j].y] += ques[j].type;
            }
        }
        ans[ques[i].id] += ques[i].type * (rangeSum(ques[i].y + 1, ques[i].z) + bound[ques[i].y]);
    }

    for (int i = headPt; i < j; i++) {
        if (ques[i].id == -1) {
            if (ques[i].y == ques[i].z)
                add(ques[i].y, -ques[i].type);
            bound[ques[i].y] -= ques[i].type;
        }
    }

    inplace_merge(ques + headPt, ques + midPt + 1, ques + tailPt + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len, qNum; cin >> len >> qNum;
    const auto initPre = [len](int i) {
        pre[i] = (i > 0 && arr[i - 1] == arr[i] ? i - 1 : i);
    };

    for (int i = 0; i < len; i++) {
        cin >> arr[i], initPre(i);
        ques[i] = {-1, 1, arr[i], i, pre[i]};
    }

    int quesPt = len, ansPt = 0;
    for (int i = 0; i < qNum; i++) {
        int op; cin >> op;
        if (op == 1) {
            // Modify
            int pos, col; cin >> pos >> col; pos--;
            ques[quesPt++] = {-1, -1, arr[pos], pos, pre[pos]};
            if (pos < len)
                ques[quesPt++] = {-1, -1, arr[pos + 1], pos + 1, pre[pos + 1]};
            arr[pos] = col; initPre(pos); 
            ques[quesPt++] = {-1, 1, arr[pos], pos, pre[pos]};
            if (pos < len)
                initPre(pos + 1), ques[quesPt++] = {-1, 1, arr[pos + 1], pos + 1, pre[pos + 1]};
        } else {
            // Query
            int qLeftPt, qRightPt, leftCol, rightCol;
            cin >> qLeftPt >> qRightPt >> leftCol >> rightCol;
            qLeftPt--; qRightPt--;
            ques[quesPt++] = {ansPt, -1, leftCol - 1, qLeftPt, qRightPt};
            ques[quesPt++] = {ansPt, 1, rightCol, qLeftPt, qRightPt};
            ansPt++;
        }
    }

    divideConquer(0, quesPt - 1);
    for (int i = 0; i < ansPt; i++)
        cout << ans[i] << '\n';

    return 0;
}