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

#define SIZE 121

long long int arr[SIZE];
long long int bitArr[SIZE][SIZE];
int len;

int getLowbit(int n)
{
    return n & -n;
}

void add(const pair<int, int> & pos, long long int val)
{
    for (int i = pos.first; i < SIZE; i += getLowbit(i))
    {
        for (int j = pos.second; j < SIZE; j += getLowbit(j))
        {
            bitArr[i][j] += val;
        }
    }
}

long long int getSum(const pair<int, int> & pos)
{
    long long int ans = 0;
    for (int i = pos.first; i > 0; i -= getLowbit(i))
    {
        for (int j = pos.second; j > 0; j -= getLowbit(j))
        {
            ans += bitArr[i][j];
        }
    }
    return ans;
}

long long int getRangeSum(const pair<int, int> & upperLeftPt, const pair<int, int> & lowerRightPt)
{
    long long int ans = getSum(lowerRightPt);

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

void init()
{
    memset(bitArr, 0, sizeof(bitArr));
    int cursorPt = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            pair<int, int> cntPos = make_pair(j + 1, i - j + 1);
            add(cntPos, arr[cursorPt]);
            cursorPt++;
            if (cursorPt == len)
                cursorPt = 0;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> len;
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
        }
        init();

        int qNum;
        cin >> qNum;
        while (qNum--)
        {
            pair<int, int> upperLeftPt, lowerRightPt;
            cin >> upperLeftPt.first >> upperLeftPt.second >> lowerRightPt.first >>lowerRightPt.second;

            long long int xNum = (lowerRightPt.first - upperLeftPt.first) / (len << 1);
            long long int yNum = (lowerRightPt.second - upperLeftPt.second) / (len << 1);
            long long int deltax = (lowerRightPt.first - upperLeftPt.first) % (len << 1);
            long long int deltay = (lowerRightPt.second - upperLeftPt.second) % (len << 1);

            upperLeftPt.first %= (len << 1);
            upperLeftPt.second %= (len << 1);
            upperLeftPt.first++;
            upperLeftPt.second++;

            long long int ans = getRangeSum(upperLeftPt, make_pair(upperLeftPt.first + deltax, upperLeftPt.second + deltay));
            
            if (xNum > 0)
            {
                ans += xNum * getRangeSum(
                    make_pair(upperLeftPt.first + deltax + 1, upperLeftPt.second),
                    make_pair(upperLeftPt.first + deltax + (len << 1), upperLeftPt.second + deltay)
                );
            }
                
            if (yNum > 0)
            {
                ans += yNum * getRangeSum(
                    make_pair(upperLeftPt.first, upperLeftPt.second + deltay + 1),
                    make_pair(upperLeftPt.first + deltax, upperLeftPt.second + deltay + (len << 1))
                );
            }

            if (xNum > 0 && yNum > 0)
            {
                ans += (xNum * yNum) * getRangeSum(
                    make_pair(upperLeftPt.first + deltax + 1, upperLeftPt.second + deltay + 1),
                    make_pair(upperLeftPt.first + deltax + (len << 1), upperLeftPt.second + deltay + (len << 1))
                );
            }
            
            cout << ans << endl;
        }
    }
    return 0;
}