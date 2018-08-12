#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define PORT_SIZE 101
#define MINE_SIZE 201
using namespace std;

int arr[PORT_SIZE][PORT_SIZE];
int vesselEx[PORT_SIZE], portEx[PORT_SIZE];
int portMatch[PORT_SIZE], portNeed[PORT_SIZE];
bool vesselVisited[PORT_SIZE], portVisited[PORT_SIZE];

int mineMap[MINE_SIZE][MINE_SIZE], vesselMine[PORT_SIZE];

int matrixSize, mineNum, mineEdgeNum, portEdgeNum;

void floyd()
{
    for (int k = 0; k < mineNum; k++)
    {
        for (int i = 0; i < mineNum; i++)
        {
            if (mineMap[i][k] == INT_MAX)
            {
                continue;
            }
            for (int j = 0; j < mineNum; j++)
            {
                if (mineMap[k][j] == INT_MAX)
                {
                    continue;
                }
                mineMap[i][j] = min(mineMap[i][j], mineMap[i][k] + mineMap[k][j]);
            }
        }
    }
}

bool canFind(int vesselId)
{
    vesselVisited[vesselId] = true;
    for (int i = 0; i < matrixSize; i++)
    {
        if (arr[vesselId][i] == -INT_MAX)
            continue;
        if (portVisited[i])
            continue;

        int delta = vesselEx[vesselId] + portEx[i] - arr[vesselId][i];
        if (delta == 0)
        {
            portVisited[i] = true;
            if (portMatch[i] == -1 || canFind(portMatch[i]))
            {
                portMatch[i] = vesselId;
                return true;
            }
        }
        else
        {
            portNeed[i] = min(portNeed[i], delta);
        }
    }
    return false;
}

int hungarian()
{
    memset(portMatch, -1, sizeof(portMatch));
    memset(portEx, 0, sizeof(portEx));

    for (int i = 0; i < matrixSize; i++)
    {
        vesselEx[i] = arr[i][0];
        for (int j = 1; j < matrixSize; j++)
        {
            vesselEx[i] = max(vesselEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            portNeed[j] = INT_MAX;
        }

        while (true)
        {
            memset(vesselVisited, false, sizeof(vesselVisited));
            memset(portVisited, false, sizeof(portVisited));

            if (canFind(i))
                break;

            int minDelta = INT_MAX;
            for (int j = 0; j < matrixSize; j++)
            {
                if (!portVisited[j])
                    minDelta = min(minDelta, portNeed[j]);
            }

            for (int j = 0; j < matrixSize; j++)
            {
                if (vesselVisited[j])
                    vesselEx[j] -= minDelta;

                if (portVisited[j])
                    portEx[j] += minDelta;
                else
                    portNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < matrixSize; i++)
    {
        if (portMatch[i] == -1)
            continue;
        ans += arr[portMatch[i]][i];
    }
    return ans;
}

int main()
{
    while (cin >> matrixSize >> mineNum >> mineEdgeNum >> portEdgeNum)
    {
        for (int i = 0; i < matrixSize; i++)
        {
            cin >> vesselMine[i];
            vesselMine[i]--;
        }

        for (int i = 0; i < mineNum; i++)
        {
            for (int j = 0; j < i; j++)
            {
                mineMap[i][j] = INT_MAX;
                mineMap[j][i] = INT_MAX;
            }
            mineMap[i][i] = 0;
        }

        for (int i = 0; i < mineEdgeNum; i++)
        {
            int from, to, length;
            cin >> from >> to >> length;
            from--;
            to--;
            if (mineMap[from][to] > length)
            {
                mineMap[from][to] = length;
                mineMap[to][from] = length;
            }
        }

        floyd();

        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                arr[i][j] = -INT_MAX;
            }
        }

        for (int i = 0; i < portEdgeNum; i++)
        {
            int port, mine, length;
            cin >> port >> mine >> length;
            port--;
            mine--;
            for (int j = 0; j < matrixSize; j++)
            {
                if (mineMap[vesselMine[j]][mine] != INT_MAX)
                {
                    arr[j][port] = -min(-arr[j][port], mineMap[vesselMine[j]][mine] + length);
                }
            }
        }

        int ans = -hungarian();
        printf("%d\n", ans);
    }
    return 0;
}

