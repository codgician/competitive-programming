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
#include <cassert>
using namespace std;

#define NUM_SIZE 30010
#define QUERY_SIZE 120040

typedef struct _Query
{
    int id, sgn;
    int leftPt, rightPt;
} Query;

Query qArr[QUERY_SIZE];
int posArr[NUM_SIZE];

int arr[NUM_SIZE], ansArr[NUM_SIZE];
int numArr[NUM_SIZE];

int luckyNum, num;
int cntLeft, cntRight, cntAns;

void add(int pos)
{
    assert(pos >= 0 && pos < num);
    if (luckyNum - arr[pos] > 0 && luckyNum - arr[pos] <= num)
        cntAns += numArr[luckyNum - arr[pos]];
    numArr[arr[pos]]++;
}

void remove(int pos)
{
    assert(pos >= 0 && pos < num);
    numArr[arr[pos]]--;
    if (luckyNum - arr[pos] > 0 && luckyNum - arr[pos] <= num)
        cntAns -= numArr[luckyNum - arr[pos]];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> num)
    {
        memset(numArr, 0, sizeof(numArr));
        memset(ansArr, 0, sizeof(ansArr));

        cin >> luckyNum;

        int blockSize = sqrt(num);
        for (int i = 0; i < num; i++)
        {
            posArr[i] = i / blockSize;
            cin >> arr[i];
        }
        
        int qNum;
        cin >> qNum;

        int qPt = 0;
        for (int i = 0; i < qNum; i++)
        {
            int fstLeft, fstRight, sndLeft, sndRight;
            cin >> fstLeft >> fstRight >> sndLeft >> sndRight;

            fstLeft--;
            fstRight--;
            sndLeft--;
            sndRight--;

            // split into four queries
            // ans = [L1, R2] - [L1, L2 - 1] - [R1 + 1, R2] + [R1 + 1, L2 - 1]
            qArr[qPt++] = {i, 1, fstLeft, sndRight};
            qArr[qPt++] = {i, -1, fstLeft, sndLeft - 1};
            qArr[qPt++] = {i, -1, fstRight + 1, sndRight};
            qArr[qPt++] = {i, 1, fstRight + 1, sndLeft - 1};
        }

        sort(qArr + 0, qArr + qPt, [](Query & fst, Query & snd) {
            if (posArr[fst.leftPt] == posArr[snd.leftPt])
                return fst.rightPt < snd.rightPt;
            return fst.leftPt < snd.leftPt;
        });

        cntLeft = 0, cntRight = -1, cntAns = 0;
        for (int i = 0; i < qPt; i++)
        {
            if (qArr[i].leftPt > qArr[i].rightPt)
                continue;

            while (qArr[i].rightPt > cntRight)
                add(++cntRight);

            while (qArr[i].rightPt < cntRight)
                remove(cntRight--);

            while (qArr[i].leftPt > cntLeft)
                remove(cntLeft++);

            while (qArr[i].leftPt < cntLeft)
                add(--cntLeft);

            ansArr[qArr[i].id] += qArr[i].sgn * cntAns;
        }

        for (int i = 0; i < qNum; i++)
        {
            cout << ansArr[i] << endl;
        }
    }

    return 0;
}