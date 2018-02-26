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
#define COLOR_NUM 50
using namespace std;

int arr[SIZE][SIZE], columnMatch[SIZE];
bool hasMentioned[COLOR_NUM], hasTried[SIZE];
int n, maxTimes;

bool canFind(int rowId, int colorId)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[rowId][i] == colorId && !hasTried[i])
        {
            hasTried[i] = true;
            if (columnMatch[i] == -1 || canFind(columnMatch[i], colorId))
            {
                columnMatch[i] = rowId;
                return true;
            }
        }
    }
    return false;
}

int hungarian(int colorId)
{
    int ans = 0;
    memset(columnMatch, -1, sizeof(columnMatch));
    for (int i = 0; i < n; i++)
    {
        memset(hasTried, false, sizeof(hasTried));
        if (canFind(i, colorId))
            ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n >> maxTimes)
    {
        if (n == 0 && maxTimes == 0)
            break;

        memset(hasMentioned, false, sizeof(hasMentioned));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> arr[i][j];
                hasMentioned[--arr[i][j]] = true;
            }
        }

        bool isFirst = true;
        for (int i = 0; i < COLOR_NUM; i++)
        {
            if (!hasMentioned[i])
                continue;
            if (hungarian(i) > maxTimes)
            {
                if (isFirst)
                    isFirst = false;
                else
                    cout << " ";
                cout << i + 1;
            }
        }
        if (isFirst)
            cout << -1;
        cout << endl;
    }
    return 0;
}
