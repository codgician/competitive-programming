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

string cntMin, cntMax;
int len, k;
bool stopFlag;

bool checkMin()
{
    if (cntMin.size() > 1 && cntMin[1] == '0')
    {
        if (cntMin[0] > cntMin[2])
            return false;
        for (int i = 2; i < len; i++)
        {
            if (cntMin[i - 1] > cntMin[i])
                return false;
        }
        return true;
    }

    for (int i = 1; i < len; i++)
    {
        if (cntMin[i - 1] > cntMin[i])
            return false;
    }
    return true;
}

bool checkMax()
{
    for (int i = 1; i < len; i++)
    {
        if (cntMax[i - 1] < cntMax[i])
            return false;
    }
    return true;
}

void dfsMin(string & cntStr, int cntPos, int cntK)
{
    if (stopFlag)
        return;

    if (cntPos == len || cntK == k)
    {
        cntMin = min(cntMin, cntStr);
        stopFlag = checkMin();
        return;
    }

    int minVal = cntStr[cntPos] - '0';
    for (int i = cntPos + 1; i < len; i++)
    {
        if (cntPos == 0 && cntStr[i] == '0')
            continue;
        minVal = min(minVal, cntStr[i] - '0');
    }

    if (minVal == cntStr[cntPos] - '0')
    {
        dfsMin(cntStr, cntPos + 1, cntK);
    }
    else
    {
        for (int i = cntPos + 1; i < len; i++)
        {
            if (cntStr[i] - '0' == minVal)
            {
                swap(cntStr[cntPos], cntStr[i]);
                dfsMin(cntStr, cntPos + 1, cntK + 1);
                swap(cntStr[cntPos], cntStr[i]);
            }
        }
    }
}

void dfsMax(string & cntStr, int cntPos, int cntK)
{
    if (stopFlag)
        return;

    if (cntPos == len || cntK == k)
    {
        cntMax = max(cntMax, cntStr);
        stopFlag = checkMax();
        return;
    }

    int maxVal = cntStr[cntPos] - '0';
    for (int i = cntPos + 1; i < len; i++)
    {
        if (cntPos == 0 && cntStr[i] - '0' == 0)
            continue;
        maxVal = max(maxVal, cntStr[i] - '0');
    }

    if (maxVal == cntStr[cntPos] - '0')
    {
        dfsMax(cntStr, cntPos + 1, cntK);
    }
    else
    {
        for (int i = cntPos + 1; i < len; i++)
        {
            if (cntStr[i] - '0' == maxVal)
            {
                swap(cntStr[cntPos], cntStr[i]);
                dfsMax(cntStr, cntPos + 1, cntK + 1);
                swap(cntStr[cntPos], cntStr[i]);
            }
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
        string str;
        cin >> str >> k;
        len = str.size();

        if (k >= len)
        {
            sort(str.begin(), str.end());

            int firstNonZero = -1;
            for (int i = 0; i < len; i++)
            {
                if (str[i] != '0')
                {
                    firstNonZero = i;
                    break;
                }
            }

            if (firstNonZero != -1 && firstNonZero != 0)
            {
                swap(str[firstNonZero], str[0]);
            }

            cout << str << " ";
            sort(str.begin(), str.end(), [](char & fst, char & snd){
                return fst > snd;
            });
            cout << str << endl;
            continue;
        }

        stopFlag = false;
        cntMin = str;
        dfsMin(str, 0, 0);

        stopFlag = false;
        cntMax = str;
        dfsMax(str, 0, 0);

        cout << cntMin << " " << cntMax << endl;
    }
    return 0;
}