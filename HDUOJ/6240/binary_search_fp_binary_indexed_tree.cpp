#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <cfloat>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 100100

const double eps = 1e-6;

typedef struct _Server
{
    int startPt, endPt;
    int price;
    int discount;
} Server;

Server arr[SIZE];

double bitArr[SIZE];

int serverNum, dayNum;

int getLowbit(int n)
{
    return n & -n;
}

void update(int pos, double val)
{
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        bitArr[i] = min(bitArr[i], val);
    }
}

double query(int pos)
{
    if (pos == 0)
        return 0;
    double ans = DBL_MAX;
    for (int i = pos; i <= dayNum; i += getLowbit(i))
    {
        ans = min(ans, bitArr[i]);
    }
    return ans;
}

bool cmp(Server & fst, Server & snd)
{
    return fst.startPt < snd.startPt;
}

bool check(double cnt)
{
    double sum = 0;
    for (int i = 1; i <= dayNum; i++)
    {
        bitArr[i] = DBL_MAX;
    }

    // Grab all individually smaller than cnt part (to make it small)
    for (int i = 1; i <= serverNum; i++)
    {
        double cntVal = arr[i].price - arr[i].discount * cnt;
        if (cntVal <= eps)
            sum += cntVal;
    }

    // Fill the remaining sections
    for (int i = 1; i <= serverNum; i++)
    {
        double prevVal = query(arr[i].startPt - 1);
        double cntVal = arr[i].price - arr[i].discount * cnt;
        if (cntVal > eps)
            update(arr[i].endPt, prevVal + cntVal);
        else
            update(arr[i].endPt, prevVal);
    }

    return sum + query(dayNum) <= eps;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> serverNum >> dayNum;
        for (int i = 1; i <= serverNum; i++)
        {
            cin >> arr[i].startPt >> arr[i].endPt >> arr[i].price >> arr[i].discount;
        }
        sort(arr + 1, arr + serverNum + 1, cmp);

        double leftPt = 0, rightPt = 1001;
        while (rightPt - leftPt > eps)
        {
            double midPt = (leftPt + rightPt) / 2;
            if (check(midPt))
                rightPt = midPt;
            else
                leftPt = midPt;
        }
        cout << fixed << setprecision(3) << rightPt << endl;
    }
    return 0;
}