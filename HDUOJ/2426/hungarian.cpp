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
#define SIZE 510
#define INF 10010
using namespace std;

int arr[SIZE][SIZE];
int stuEx[SIZE], roomEx[SIZE];
int roomMatch[SIZE], roomNeed[SIZE];
bool stuVisited[SIZE], roomVisited[SIZE];
int stuNum, roomNum;

bool canFind(int stuId)
{
    stuVisited[stuId] = true;
    for (int i = 0; i < roomNum; i++)
    {
        if (arr[stuId][i] < 0)
            continue;

        if (roomVisited[i])
            continue;

        int delta = stuEx[stuId] + roomEx[i] - arr[stuId][i];
        if (delta == 0)
        {
            roomVisited[i] = true;
            if (roomMatch[i] == -1 || canFind(roomMatch[i]))
            {
                roomMatch[i] = stuId;
                return true;
            }
        }
        else
        {
            roomNeed[i] = min(roomNeed[i], delta);
        }
    }
    return false;
}

int hungarain()
{
    memset(roomMatch, -1, sizeof(roomMatch));
    memset(roomEx, 0, sizeof(roomEx));
    for (int i = 0; i < stuNum; i++)
    {
        stuEx[i] = arr[i][0];
        for (int j = 1; j < roomNum; j++)
        {
            stuEx[i] = max(stuEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < stuNum; i++)
    {
        for (int j = 0; j < roomNum; j++)
            roomNeed[j] = INF;

        while (true)
        {
            memset(roomVisited, false, sizeof(roomVisited));
            memset(stuVisited, false, sizeof(stuVisited));

            if (canFind(i))
                break;

            int minDelta = INF;
            for (int j = 0; j < roomNum; j++)
            {
                if (!roomVisited[j])
                    minDelta = min(minDelta, roomNeed[j]);
            }

            if (minDelta == INF)
                return -1;

            for (int j = 0; j < roomNum; j++)
            {
                if (stuVisited[j])
                    stuEx[j] -= minDelta;

                if (roomVisited[j])
                    roomEx[j] += minDelta;
                else
                    roomNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < roomNum; i++)
    {
        if (roomMatch[i] == -1)
            continue;
        if (arr[roomMatch[i]][i] == -INF)
            return -1;
        ans += arr[roomMatch[i]][i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int rateNum;
    int casePt = 1;
    while (cin >> stuNum >> roomNum >> rateNum)
    {
        for (int i = 0; i < stuNum; i++)
        {
            for (int j = 0; j < roomNum; j++)
            {
                arr[i][j] = -INF;
            }
        }

        for (int i = 0; i < rateNum; i++)
        {
            int stuId, roomId;
            cin >> stuId >> roomId;
            cin >> arr[stuId][roomId];
            if (arr[stuId][roomId] < 0)
                arr[stuId][roomId] = -INF;
        }

        int ans = hungarain();
        cout << "Case " << casePt++ << ": " << ans << endl;
    }
    return 0;
}
