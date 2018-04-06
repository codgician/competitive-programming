#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 100010
using namespace std;

typedef struct _Node
{
    long long int x, y;
} Node;

Node arr[SIZE], sndSeg[SIZE];

bool sameSegment(Node &a, Node &b, Node &c)
{
    return (a.y - b.y) * (a.x - c.x) == (a.x - b.x) * (a.y - c.y);
}

int main()
{
    ios::sync_with_stdio(false);
    int num;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        cin >> arr[i].x >> arr[i].y;
    }

    if (num <= 4)
    {
        cout << "YES" << endl;
        return 0;
    }

    bool ans = false;
    for (int t = 0; t < 3; t++)
    {
        Node fstPt, sndPt;
        if (t == 0)
        {
            fstPt = arr[0];
            sndPt = arr[1];
        }
        else if (t == 1)
        {
            fstPt = arr[0];
            sndPt = arr[2];
        }
        else if (t == 2)
        {
            fstPt = arr[1];
            sndPt = arr[2];
        }

        int sndSegPt = 0;
        for (int i = 0; i < num; i++)
        {
            if (!sameSegment(fstPt, sndPt, arr[i]))
            {
                sndSeg[sndSegPt++] = arr[i];
            }
        }

        int cntAns = true;
        if (sndSegPt > 2)
        {
            for (int i = 2; i < sndSegPt; i++)
            {
                if (!sameSegment(sndSeg[0], sndSeg[1], sndSeg[i]))
                {
                    cntAns = false;
                    break;
                }
            }
        }

        if (cntAns)
        {
            ans = true;
            break;
        }
    }

    if (ans)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}
