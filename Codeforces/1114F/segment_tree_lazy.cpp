#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <bitset>
#include <cassert>
using namespace std;

#define SIZE 400010
#define PRIME_SIZE 310
#define PRIME_NUM 63

const long long int mod = 1e9 + 7;

int arr[SIZE];
bitset<PRIME_NUM> bstArr[SIZE];

long long int invArr[PRIME_SIZE];

void initInv()
{
    invArr[1] = 1;
    for (int i = 2; i < PRIME_SIZE; i++)
        invArr[i] = (mod - mod / i) * invArr[mod % i] % mod;
}

long long int fastPow(long long int a, int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

int primeArr[PRIME_SIZE], minFacArr[PRIME_SIZE], primePt;

void initPrime()
{
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    for (int i = 2; i < PRIME_SIZE; i++)
    {
        if (minFacArr[i] == 0)
        {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (PRIME_SIZE - 1) / i); j++)
            minFacArr[i * primeArr[j]] = primeArr[j];
    }
}

#define LEFT_SON (segPt << 1)
#define RIGHT_SON (segPt << 1 | 1)

typedef struct _SegNode
{
    int leftPt, rightPt;
    long long int prod, prodLazy;
    bitset<PRIME_NUM> bst, bstLazy;
} SegNode;

SegNode segTree[SIZE << 2];

void pushUp(int segPt)
{
    segTree[segPt].prod = segTree[LEFT_SON].prod * segTree[RIGHT_SON].prod % mod;
    segTree[segPt].bst = segTree[LEFT_SON].bst | segTree[RIGHT_SON].bst;
}

void pushDown(int segPt)
{
    if (segTree[segPt].bstLazy.none())
        return;

    segTree[LEFT_SON].prod = segTree[LEFT_SON].prod * fastPow(segTree[segPt].prodLazy, segTree[LEFT_SON].rightPt - segTree[LEFT_SON].leftPt + 1) % mod;
    segTree[LEFT_SON].bst |= segTree[segPt].bstLazy;
    segTree[RIGHT_SON].prod = segTree[RIGHT_SON].prod * fastPow(segTree[segPt].prodLazy, segTree[RIGHT_SON].rightPt - segTree[RIGHT_SON].leftPt + 1) % mod;
    segTree[RIGHT_SON].bst |= segTree[segPt].bstLazy;


    segTree[LEFT_SON].prodLazy = segTree[LEFT_SON].prodLazy * segTree[segPt].prodLazy % mod;
    segTree[LEFT_SON].bstLazy |= segTree[segPt].bstLazy;
    segTree[RIGHT_SON].prodLazy = segTree[RIGHT_SON].prodLazy * segTree[segPt].prodLazy % mod;
    segTree[RIGHT_SON].bstLazy |= segTree[segPt].bstLazy;

    segTree[segPt].prodLazy = 1;
    segTree[segPt].bstLazy.reset();
}

void build(int segPt, int leftPt, int rightPt)
{
    segTree[segPt].leftPt = leftPt;
    segTree[segPt].rightPt = rightPt;
    if (leftPt == rightPt)
    {
        segTree[segPt].bst = bstArr[arr[leftPt]];
        segTree[segPt].bstLazy.reset();
        segTree[segPt].prod = arr[leftPt];
        segTree[segPt].prodLazy = 1;
        return;
    }
    int midPt = (leftPt + rightPt) >> 1;
    build(LEFT_SON, leftPt, midPt);
    build(RIGHT_SON, midPt + 1, rightPt);
    pushUp(segPt);
    segTree[segPt].bstLazy.reset();
    segTree[segPt].prodLazy = 1;
}

void rangeMultiply(int segPt, int qLeftPt, int qRightPt, int val)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        segTree[segPt].prod = segTree[segPt].prod * fastPow(val, segTree[segPt].rightPt - segTree[segPt].leftPt + 1) % mod;
        segTree[segPt].prodLazy = segTree[segPt].prodLazy * val % mod;
        segTree[segPt].bst |= bstArr[val];
        segTree[segPt].bstLazy |= bstArr[val];
        return;
    }
    pushDown(segPt);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
        rangeMultiply(LEFT_SON, qLeftPt, qRightPt, val);
    if (qRightPt > midPt)
        rangeMultiply(RIGHT_SON, qLeftPt, qRightPt, val);
    pushUp(segPt);
}

pair<long long int, bitset<PRIME_NUM>> queryTotient(int segPt, int qLeftPt, int qRightPt)
{
    if (segTree[segPt].leftPt >= qLeftPt && segTree[segPt].rightPt <= qRightPt)
    {
        return make_pair(segTree[segPt].prod, segTree[segPt].bst);
    }
    pushDown(segPt);

    pair<long long int, bitset<PRIME_NUM>> ans = make_pair(1, 0);
    int midPt = (segTree[segPt].leftPt + segTree[segPt].rightPt) >> 1;
    if (qLeftPt <= midPt)
    {
        pair<long long int, bitset<PRIME_NUM>> ret = queryTotient(LEFT_SON, qLeftPt, qRightPt);
        ans.first =  ans.first * ret.first % mod;
        ans.second |= ret.second;
    }
    if (qRightPt > midPt)
    {
        pair<long long int, bitset<PRIME_NUM>> ret = queryTotient(RIGHT_SON, qLeftPt, qRightPt);
        ans.first = ans.first * ret.first % mod;
        ans.second |= ret.second;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initPrime();
    initInv();
    bstArr[1].reset();
    for (int t = 2; t <= 300; t++)
    {
        int cnt = t;
        bstArr[t].reset();

        for (int i = 0; i < primePt && primeArr[i] * primeArr[i] <= cnt; i++)
        {
            if (cnt % primeArr[i] > 0)
                continue;
            bstArr[t].set(i, 1);
            cnt /= primeArr[i];
            while (cnt % primeArr[i] == 0)
                cnt /= primeArr[i];
        }
        if (cnt > 1)
        {
            int indx = lower_bound(primeArr + 0, primeArr + primePt, cnt) - primeArr;
            bstArr[t].set(indx);
        }
    }

    int len, qNum;
    cin >> len >> qNum;
    for (int i = 1; i <= len; i++)
        cin >> arr[i];
    build(1, 1, len);

    while (qNum--)
    {
        string opr;
        int qLeftPt, qRightPt;
        cin >> opr >> qLeftPt >> qRightPt;
        if (opr[0] == 'T')
        {
            // Totient
            pair<long long int, bitset<PRIME_NUM>> ret = queryTotient(1, qLeftPt, qRightPt);

            long long int ans = ret.first;
            for (int i = 0; i < PRIME_NUM; i++)
            {
                if (!ret.second[i])
                    continue;
                ans = ans * (primeArr[i] - 1) % mod * invArr[primeArr[i]] % mod;
            }
            cout << ans << '\n';
        }
        else if (opr[0] == 'M')
        {
            // Multiply
            int val;
            cin >> val;
            if (val == 1)
                continue;
            rangeMultiply(1, qLeftPt, qRightPt, val);
        }
    }

    return 0;
}