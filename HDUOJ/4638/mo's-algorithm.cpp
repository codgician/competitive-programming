#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 100010
using namespace std;

typedef struct _Query
{
    int id;
    int leftPt, rightPt;
    int ans;
} Query;

int arr[SIZE], posArr[SIZE];
Query qArr[SIZE];

bool cntStatus[SIZE];
int len, cntAns;

bool cmp(Query &fst, Query &snd)
{
    if (posArr[fst.leftPt] != posArr[snd.leftPt])
        return fst.leftPt < snd.leftPt;
    return fst.rightPt < snd.rightPt;
}

bool restoreCmp(Query &fst, Query &snd)
{
    return fst.id < snd.id;
}

void add(int cntPt)
{
    if (cntPt < 0 || cntPt > len - 1)
        return;

    cntStatus[arr[cntPt]] = true;

    if (cntStatus[arr[cntPt] - 1] && cntStatus[arr[cntPt] + 1])
        cntAns--;
    else if (!cntStatus[arr[cntPt] - 1] && !cntStatus[arr[cntPt] + 1])
        cntAns++;
}

void remove(int cntPt)
{
    if (cntPt < 0 || cntPt > len - 1)
        return;

    cntStatus[arr[cntPt]] = false;

    if (cntStatus[arr[cntPt] - 1] && cntStatus[arr[cntPt] + 1])
        cntAns++;
    else if (!cntStatus[arr[cntPt] - 1] && !cntStatus[arr[cntPt] + 1])
        cntAns--;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(cntStatus, false, sizeof(cntStatus));
        int qNum;
        cin >> len >> qNum;
        int blockNum = sqrt(len);
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
            posArr[i] = i / blockNum;
        }

        for (int i = 0; i < qNum; i++)
        {
            cin >> qArr[i].leftPt >> qArr[i].rightPt;
            qArr[i].leftPt--;
            qArr[i].rightPt--;
            qArr[i].id = i;
        }

        sort(qArr + 0, qArr + qNum, cmp);
        cntAns = 0;
        int cntLeftPt = 1, cntRightPt = 0;
        for (int i = 0; i < qNum; i++)
        {
            if (qArr[i].rightPt < cntLeftPt || qArr[i].leftPt > cntRightPt)
            {
                for (int i = cntLeftPt; i <= cntRightPt; i++)
                {
                    cntStatus[arr[i]] = false;
                }
                cntAns = 0;
                cntLeftPt = qArr[i].leftPt;
                cntRightPt = qArr[i].rightPt;
                for (int i = cntLeftPt; i <= cntRightPt; i++)
                {
                    add(i);
                }

                qArr[i].ans = cntAns;
                continue;
            }

            while (cntLeftPt < qArr[i].leftPt)
                remove(cntLeftPt++);
            while (cntLeftPt > qArr[i].leftPt)
                add(--cntLeftPt);
            while (cntRightPt < qArr[i].rightPt)
                add(++cntRightPt);
            while (cntRightPt > qArr[i].rightPt)
                remove(cntRightPt--);

            qArr[i].ans = cntAns;
        }

        sort(qArr + 0, qArr + qNum, restoreCmp);
        for (int i = 0; i < qNum; i++)
        {
            cout << qArr[i].ans << endl;
        }
    }
    return 0;
}
