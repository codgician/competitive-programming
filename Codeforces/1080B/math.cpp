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

long long int sum[2];

long long int getSum(long long int fst, long long int lst)
{
    if (fst > lst)
        return 0;
    return ((fst + lst) * (((lst - fst) >> 1) + 1)) >> 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        long long int qLeftPt, qRightPt;
        cin >> qLeftPt >> qRightPt;

        if ((qLeftPt & 1) == (qRightPt & 1))
        {
            sum[qLeftPt & 1] = getSum(qLeftPt, qRightPt);
            sum[!(qLeftPt & 1)] = getSum(qLeftPt + 1, qRightPt - 1);
        }
        else
        {
            sum[qLeftPt & 1] = getSum(qLeftPt, qRightPt - 1);
            sum[qRightPt & 1] = getSum(qLeftPt + 1, qRightPt);
        }

        cout << sum[0] - sum[1] << endl;
    }

    return 0;
}