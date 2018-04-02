#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 1010
using namespace std;

int oneNumBit[SIZE][SIZE];

int getLowbit(int n)
{
    return n & -n;
}

void add(pair<int, int> pos, int val)
{
    for (int i = pos.first; i < SIZE; i += getLowbit(i))
    {
        for (int j = pos.second; j < SIZE; j += getLowbit(j))
        {
            oneNumBit[i][j] += val;
        }
    }
}

int getSum(pair<int, int> pos)
{
    int ans = 0;
    for (int i = pos.first; i > 0; i -= getLowbit(i))
    {
        for (int j = pos.second; j > 0; j -= getLowbit(j))
        {
            ans += oneNumBit[i][j];
        }
    }
    return ans;
}

int rangeAdd(pair<int, int> upperLeftPt, pair<int, int> lowerRightPt, int val)
{
    add(upperLeftPt, val);
    add(make_pair(lowerRightPt.first + 1, lowerRightPt.second + 1), val);

    add(make_pair(upperLeftPt.first, lowerRightPt.second + 1), -val);
    add(make_pair(lowerRightPt.first + 1, upperLeftPt.second), -val);
}

int getRangeSum(pair<int, int> upperLeftPt, pair<int, int> lowerRightPt)
{
    int ans = getSum(lowerRightPt);

    if (upperLeftPt.first > 0)
    {
        ans -= getSum(make_pair(upperLeftPt.first - 1, lowerRightPt.second));
    }
    if (upperLeftPt.second > 0)
    {
        ans -= getSum(make_pair(lowerRightPt.first, upperLeftPt.second - 1));
    }
    if (upperLeftPt.first > 0 && upperLeftPt.second > 0)
    {
        ans += getSum(make_pair(upperLeftPt.first - 1, upperLeftPt.second - 1));
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(oneNumBit, 0, sizeof(oneNumBit));
        int matrixSize, queryNum;
        cin >> matrixSize >> queryNum;
        while (queryNum--)
        {
            char opr;
            cin >> opr;
            if (opr == 'C')
            {
                pair<int, int> upperLeftPt, lowerRightPt;
                cin >> upperLeftPt.first >> upperLeftPt.second >> lowerRightPt.first >> lowerRightPt.second;
                rangeAdd(upperLeftPt, lowerRightPt, 1);
            }
            else if (opr == 'Q')
            {
                pair<int, int> cntPt;
                cin >> cntPt.first >> cntPt.second;

                int ans = getSum(cntPt);
                cout << (ans & 1) << endl;
            }
        }

        if (caseNum > 0)
            cout << endl;
    }
    return 0;
}
