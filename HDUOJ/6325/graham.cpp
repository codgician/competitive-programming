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

#define SIZE 200100

typedef struct _Vertex
{
    long long int x, y;
    int id;
} Vertex;

Vertex arr[SIZE];
int convexHull[SIZE], convexHullPt;
bool hasVisited[SIZE];
int ans[SIZE];
int num;

long long int getCrossedProd(const Vertex & fst, const Vertex & snd)
{
    return fst.x * snd.y - snd.x * fst.y;
}

double getDis(const Vertex & fst, const Vertex & snd)
{
    return sqrt(pow(fst.x - snd.x, 2) + pow(fst.y - snd.y, 2));
}

Vertex vertexMinus(const Vertex & fst, const Vertex & snd)
{
    Vertex ans = {fst.x - snd.x, fst.y - snd.y};
    return ans;
}

bool isLeft(const Vertex & fst, const Vertex & snd, const Vertex & thd)
{
    return getCrossedProd(vertexMinus(snd, fst), vertexMinus(thd, fst)) > 0;
}

void graham()
{
    convexHullPt = 0;
    for (int i = 0; i < num; i++)
    {
        if (i > 0 && arr[i].x == arr[i - 1].x)
            continue;
        while (convexHullPt > 1 && isLeft(arr[convexHull[convexHullPt - 2]], arr[convexHull[convexHullPt - 1]], arr[i]))
            convexHullPt--;
        convexHull[convexHullPt++] = i;
    }
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        scanf("%d", &num);
        for (int i = 0; i < num; i++)
        {
            scanf("%lld%lld", &arr[i].x, &arr[i].y);
            arr[i].id = i + 1;
        }

        sort(arr + 0, arr + num, [](Vertex & fst, Vertex & snd) {
            if (fst.x == snd.x)
            {
                if (fst.y == snd.y)
                    return fst.id < snd.id;
                return fst.y > snd.y;
            }
            return fst.x < snd.x;
        });

        graham();

        memset(hasVisited, false, sizeof(hasVisited));
        ans[0] = 1;
        ans[convexHullPt - 1] = num;
        hasVisited[0] = true;
        hasVisited[convexHullPt - 1] = true;
        for (int i = 1; i < convexHullPt - 1; i++)
        {
            if (getCrossedProd(vertexMinus(arr[convexHull[i]], arr[convexHull[i - 1]]), 
            vertexMinus(arr[convexHull[i + 1]], arr[convexHull[i - 1]])) != 0)
            {
                hasVisited[i] = true;
            }
        }

        for (int i = convexHullPt - 2; i > 0; i--)
        {
            if (hasVisited[i])
                ans[i] = arr[convexHull[i]].id;
            else
                ans[i] = min(ans[i + 1], arr[convexHull[i]].id);
        }

        for (int i = 0; i < convexHullPt; i++)
        {
            if (ans[i] != arr[convexHull[i]].id)
                continue;
            printf("%d", ans[i]);
            if (i < convexHullPt - 1)
                printf(" ");
            else
                printf("\n");
        }
    }
    return 0;
}