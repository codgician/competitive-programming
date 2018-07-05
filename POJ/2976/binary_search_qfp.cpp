#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
using namespace std;

#define SIZE 1010

const double eps = 1e-6;

typedef struct _Test
{
    int done;
    int tot;
} Test;

Test arr[SIZE];
double tmpArr[SIZE];

int testNum, dropNum;

bool cmpRule(double fst, double snd)
{
    return fst > snd;
}

bool judge(double cnt)
{
    for (int i = 0; i < testNum; i++)
    {
        tmpArr[i] = (double)arr[i].done - cnt * arr[i].tot;
    }
    sort(tmpArr + 0, tmpArr + testNum, cmpRule);

    double ans = 0;
    for (int i = 0; i < testNum - dropNum; i++)
    {
        ans += tmpArr[i];
    }

    return ans >= 0;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> testNum >> dropNum)
    {
        if (testNum == 0 && dropNum == 0)
            break;

        for (int i = 0; i < testNum; i++)
            cin >> arr[i].done;
        for (int i = 0; i < testNum; i++)
            cin >> arr[i].tot;

        double leftPt = 0, rightPt = 1;
        while (rightPt - leftPt > eps)
        {
            double midPt = (leftPt + rightPt) / 2;
            if (judge(midPt))
                leftPt = midPt;
            else
                rightPt = midPt;
        }

        cout << fixed << setprecision(0) << leftPt * 100 << endl;
    }
    return 0;
}