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
using namespace std;

#define SIZE 200010

typedef struct _Node
{
    int leftPt, rightPt;
} Node;

Node arr[SIZE];
int leftArr[SIZE], rightArr[SIZE], rangeArr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    while (cin >> num)
    {
        memset(leftArr, 0, sizeof(leftArr));
        memset(rightArr, 0, sizeof(rightArr));
        memset(rangeArr, 0, sizeof(rangeArr));

        int len = -1;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].leftPt >> arr[i].rightPt;

            leftArr[arr[i].leftPt]++;
            rightArr[arr[i].rightPt]++;
            rangeArr[arr[i].leftPt]++;
            rangeArr[arr[i].rightPt]--;

            len = max(len, arr[i].rightPt + 1);
        }

        for (int i = 1; i < len; i++)
        {
            leftArr[i] += leftArr[i - 1];
            rightArr[i] += rightArr[i - 1];
            rangeArr[i] += rangeArr[i - 1];
        }

        int fstAns = 0;
        for (int i = 0; i < num; i++)
        {
            fstAns = max(fstAns, num - rightArr[arr[i].leftPt] - (leftArr[len - 1] - leftArr[arr[i].rightPt - 1]));
        }

        int sndAns = 0;
        for (int i = 0; i < len; i++)
        {
            sndAns = max(sndAns, rangeArr[i]);
        }

        cout << fstAns << " " << sndAns << endl;
    }

    return 0;
}