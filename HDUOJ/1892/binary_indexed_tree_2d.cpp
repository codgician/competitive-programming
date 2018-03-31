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

int bitArr[SIZE][SIZE];

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
            bitArr[i][j] += val;
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
            ans += bitArr[i][j];
        }
    }
    return ans;
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
    for (int t = 1; t <= caseNum; t++)
    {
        memset(bitArr, 0, sizeof(bitArr));
        for (int i = 1; i < SIZE; i++)
        {
            for (int j = 1; j < SIZE; j++)
            {
                add(make_pair(i, j), 1);
            }
        }

        int queryNum;
        cin >> queryNum;
        cout << "Case " << t << ":" << endl;
        while (queryNum--)
        {
            char opr;
            cin >> opr;
            if (opr == 'S')
            {
                pair<int, int> startPos, endPos;
                cin >> startPos.first >> startPos.second >> endPos.first >> endPos.second;
                startPos.first++;
                startPos.second++;
                endPos.first++;
                endPos.second++;

                if (startPos.first > endPos.first)
                    swap(startPos.first, endPos.first);
                if (startPos.second > endPos.second)
                    swap(startPos.second, endPos.second);

                int ans = getRangeSum(startPos, endPos);
                cout << ans << endl;
            }
            else if (opr == 'A')
            {
                pair<int, int> cntPos;
                int bookNum;
                cin >> cntPos.first >> cntPos.second >> bookNum;
                cntPos.first++;
                cntPos.second++;

                add(cntPos, bookNum);
            }
            else if (opr == 'D')
            {
                pair<int, int> cntPos;
                int bookNum;
                cin >> cntPos.first >> cntPos.second >> bookNum;
                cntPos.first++;
                cntPos.second++;

                int cntPosNum = getRangeSum(cntPos, cntPos);
                bookNum = min(bookNum, cntPosNum);
                add(cntPos, -bookNum);
            }
            else if (opr == 'M')
            {
                pair<int, int> startPos, endPos;
                int bookNum;
                cin >> startPos.first >> startPos.second >> endPos.first >> endPos.second >> bookNum;
                startPos.first++;
                startPos.second++;
                endPos.first++;
                endPos.second++;

                int startPosNum = getRangeSum(startPos, startPos);
                bookNum = min(bookNum, startPosNum);
                add(startPos, -bookNum);
                add(endPos, bookNum);
            }
        }
    }
    return 0;
}
