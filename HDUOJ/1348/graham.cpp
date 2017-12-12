#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#define SIZE 101
#define PI 3.14159
using namespace std;

typedef struct _Dot {
    int x;
    int y;
} dot;

dot arr[SIZE];

int getCrossedProduct(dot a, dot b)
{
    return a.x * b.y - b.x * a.y;
}

double getDistance(dot a, dot b)
{
    return sqrt((double)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

dot dotMinus(dot a, dot b)
{
    dot ans;
    ans.x = a.x - b.x;
    ans.y = a.y - b.y;
    return ans;
}

bool isLeft(dot a, dot b, dot c)
{
    return getCrossedProduct(dotMinus(b, a), dotMinus(c, a)) > 0;
}

bool cmpRule(dot a, dot b)
{
    int crossedProduct = getCrossedProduct(dotMinus(a, arr[0]), dotMinus(b, arr[0]));
    if (crossedProduct < 0)
        return false;
    else if (crossedProduct == 0 && getDistance(a, arr[0]) < getDistance(b, arr[0]))
        return false;
    else
        return true;
}

// Maintain a stack.
dot graham[SIZE];
int arrPt = 0;

void push(dot n)
{
    graham[arrPt] = n;
    arrPt++;
}

void pop()
{
    arrPt--;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    scanf("%d", &caseNum);
    for (int t = 0; t < caseNum; t++)
    {
        int dotNum, R;
        scanf("%d%d", &dotNum, &R);
        double ans = 0;
        if (dotNum == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            ans = 0;
        }
        else if (dotNum == 2)
        {
            dot a, b;
            scanf("%d%d%d%d", &a.x, &a.y, &b.x, &b.y);
            ans = getDistance(a, b);
        }
        else
        {
            // Find the point with the minimum y coordinate.
            int lowestdotIndex = 0;
            dot lowestdot;
            lowestdot.y = INT_MAX;
            for (int i = 0; i < dotNum; i++)
            {
                scanf("%d%d", &arr[i].x, &arr[i].y);
                if (arr[i].y < lowestdot.y || (arr[i].y == lowestdot.y && arr[i].x < lowestdot.x))
                {
                    lowestdotIndex = i;
                    lowestdot = arr[i];
                }
            }
            swap(arr[0], arr[lowestdotIndex]);

            // Sort it!
            sort(arr + 1, arr + dotNum, cmpRule);

            arrPt = 0;
            push(arr[0]);
            push(arr[1]);
            push(arr[2]);

            for (int i = 3; i < dotNum; i++)
            {
                while (!isLeft(graham[arrPt - 2], graham[arrPt - 1], arr[i]) && arrPt > 2)
                {
                    pop();
                }
                push(arr[i]);
            }

            for (int i = 0; i < arrPt - 1; i++)
            {
                ans += getDistance(graham[i], graham[i + 1]);
            }
            ans += getDistance(graham[0], graham[arrPt - 1]);
        }
        ans += PI * R * 2;
        printf("%.0lf\n", ans);
        if (t < caseNum - 1)
            printf("\n");
    }
    return 0;
}
