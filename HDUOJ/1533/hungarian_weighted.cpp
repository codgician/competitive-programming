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
#define SIZE 101
using namespace std;

typedef pair<int, int> Node;

int arr[SIZE][SIZE];
Node man[SIZE], house[SIZE];
int manEx[SIZE], houseEx[SIZE];
int houseMatch[SIZE], houseNeed[SIZE];
bool manVisited[SIZE], houseVisited[SIZE];
int housePt, manPt;

bool canFind(int manId)
{
    manVisited[manId] = true;
    for (int i = 0; i < manPt; i++)
    {
        if (houseVisited[i])
            continue;

        int delta = manEx[manId] + houseEx[i] - arr[manId][i];
        if (delta == 0)
        {
            houseVisited[i] = true;
            if (houseMatch[i] == -1 || canFind(houseMatch[i]))
            {
                houseMatch[i] = manId;
                return true;
            }
        }
        else
        {
            houseNeed[i] = min(houseNeed[i], delta);
        }
    }
    return false;
}

int hungarian()
{
    memset(houseMatch, -1, sizeof(houseMatch));
    memset(houseEx, 0, sizeof(houseEx));
    memset(manEx, 0, sizeof(manEx));

    for (int i = 0; i < manPt; i++)
    {
        for (int j = 0; j < housePt; j++)
        {
            manEx[i] = max(manEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < manPt; i++)
    {
        for (int j = 0; j < housePt; j++)
            houseNeed[j] = INT_MAX;

        while (true)
        {
            memset(manVisited, false, sizeof(manVisited));
            memset(houseVisited, false, sizeof(houseVisited));

            if (canFind(i))
                break;

            int minDelta = INT_MAX;
            for (int j = 0; j < housePt; j++)
            {
                if (!houseVisited[j])
                    minDelta = min(minDelta, houseNeed[j]);
            }

            for (int j = 0; j < manPt; j++)
            {
                if (manVisited[j])
                    manEx[j] -= minDelta;
            }

            for (int j = 0; j < housePt; j++)
            {
                if (houseVisited[j])
                    houseEx[j] += minDelta;
                else
                    houseNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < housePt; i++)
    {
        if (houseMatch[i] != -1)
            ans += arr[houseMatch[i]][i];
    }
    return ans;
}

int getDistance(Node &i, Node &j)
{
    return abs(i.first - j.first) + abs(i.second - j.second);
}

int main()
{
    ios::sync_with_stdio(false);
    int row, column;
    while (cin >> row >> column)
    {
        if (row == 0 && column == 0)
            break;

        // In this problem, manPt == housePt
        manPt = 0;
        housePt = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                char ch;
                cin >> ch;
                if (ch == 'm')
                {
                    man[manPt++] = make_pair(i, j);
                }
                else if (ch == 'H')
                {
                    house[housePt++] = make_pair(i, j);
                }
            }
        }

        memset(arr, 0, sizeof(arr));
        for (int i = 0; i < manPt; i++)
        {
            for (int j = 0; j < housePt; j++)
            {
                arr[i][j] = -getDistance(man[i], house[j]);
            }
        }

        int ans = -hungarian();
        cout << ans << endl;
    }
}
