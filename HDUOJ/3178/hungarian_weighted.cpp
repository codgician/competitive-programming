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
#define SIZE 26
#define INF 10010
using namespace std;

int arr[SIZE][SIZE];
int objEx[SIZE], catEx[SIZE];
int catMatch[SIZE], catNeed[SIZE];
bool objVisited[SIZE], catVisited[SIZE];
int stdAns[INF];

const int matrixSize = 26;

bool canFind(int objId)
{
    objVisited[objId] = true;
    for (int i = 0; i < matrixSize; i++)
    {
        if (catVisited[i])
            continue;

        int delta = objEx[objId] + catEx[i] - arr[objId][i];
        if (delta == 0)
        {
            catVisited[i] = true;
            if (catMatch[i] == -1 || canFind(catMatch[i]))
            {
                catMatch[i] = objId;
                return true;
            }
        }
        else
        {
            catNeed[i] = min(catNeed[i], delta);
        }
    }
    return false;
}

int hungarian()
{
    memset(catMatch, -1, sizeof(catMatch));
    memset(catEx, 0, sizeof(catEx));

    for (int i = 0; i < matrixSize; i++)
    {
        objEx[i] = arr[i][0];
        for (int j = 1; j < matrixSize; j++)
        {
            objEx[i] = max(objEx[i], arr[i][j]);
        }
    }

    for (int i = 0; i < matrixSize; i++)
    {
        if (objEx[i] == 0)
            continue;

        for (int j = 0; j < matrixSize; j++)
            catNeed[j] = INF;

        while (true)
        {
            memset(objVisited, false, sizeof(objVisited));
            memset(catVisited, false, sizeof(catVisited));

            if (canFind(i))
                break;

            int minDelta = INF;
            for (int j = 0; j < matrixSize; j++)
            {
                if (!catVisited[j])
                    minDelta = min(minDelta, catNeed[j]);
            }

            for (int j = 0; j < matrixSize; j++)
            {
                if (objVisited[j])
                    objEx[j] -= minDelta;

                if (catVisited[j])
                    catEx[j] += minDelta;
                else
                    catNeed[j] -= minDelta;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < matrixSize; i++)
    {
        if (catMatch[i] == -1)
            continue;
        ans += arr[catMatch[i]][i];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int objNum, catNum, stuNum;
        cin >> objNum >> catNum >> stuNum;
        for (int i = 0; i < objNum; i++)
        {
            char ch;
            cin >> ch;
            stdAns[i] = ch - 'A';
        }

        while (stuNum--)
        {
            memset(arr, 0, sizeof(arr));
            for (int i = 0; i < objNum; i++)
            {
                char ch;
                cin >> ch;
                arr[stdAns[i]][ch - 'A']++;
            }

            double ans = (double)hungarian() / objNum;
            cout << fixed << setprecision(4) << ans << endl;
        }
    }
    return 0;
}
