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

#define SIZE 1010

const double eps = 1e-6;

typedef struct _Vertex
{
    int x, y;
    int height;
} Vertex;

Vertex vArr[SIZE];

typedef struct _Edge
{
    double len;
    int cost;
    double cntLen;
} Edge;

Edge arr[SIZE][SIZE];

bool hasVisited[SIZE];
double dis[SIZE];

int vertexNum;

inline double getDis(Vertex & fst, Vertex & snd)
{
    return sqrt((fst.x - snd.x) * (fst.x - snd.x) + (fst.y - snd.y) * (fst.y - snd.y));
}

inline double prim(int startPt)
{
    double ans = 0;
    for (int i = 0; i < vertexNum; i++)
    {
        hasVisited[i] = false;
        dis[i] = DBL_MAX;
    }
    dis[startPt] = 0;

    for (int t = 0; t < vertexNum; t++)
    {
        double minDis = DBL_MAX;
        int minPt = -1;
        for (int i = 0; i < vertexNum; i++)
        {
            if (hasVisited[i])
                continue;

            if (dis[i] < minDis)
            {
                minDis = dis[i];
                minPt = i;
            }
        }

        if (minPt == -1)
            break;
        hasVisited[minPt] = true;
        ans += dis[minPt];

        for (int i = 0; i < vertexNum; i++)
        {
            if (hasVisited[i])
                continue;
            dis[i] = min(dis[i], arr[minPt][i].cntLen);
        }
    }

    return ans;
}


inline bool check(double cnt)
{
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < i; j++)
        {
            arr[i][j].cntLen = arr[i][j].cost - cnt * arr[i][j].len;
            arr[j][i].cntLen = arr[i][j].cntLen;
        }
        arr[i][i].cntLen = 0;
    }

    return prim(0) > eps;
}

int main()
{
    while (cin >> vertexNum)
    {
        if (vertexNum == 0)
            break;

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> vArr[i].x >> vArr[i].y >> vArr[i].height;
            for (int j = 0; j < i; j++)
            {
                arr[j][i].len = getDis(vArr[i], vArr[j]);
                arr[j][i].cost = abs(vArr[i].height - vArr[j].height);
                arr[i][j] = arr[j][i];
            }
        }

        double leftPt = 0, rightPt = 100;
        while (rightPt - leftPt > eps)
        {
            double midPt = (leftPt + rightPt) / 2;
            if (check(midPt))
                leftPt = midPt;
            else
                rightPt = midPt;
        }
        cout << fixed << setprecision(3) << leftPt << endl;
    }
    return 0;
}