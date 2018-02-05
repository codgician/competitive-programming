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
#define SIZE 101
using namespace std;

int arr[SIZE][SIZE], path[SIZE][SIZE];
int point[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int cityNum;
        cin >> cityNum;
        for (int i = 0; i < cityNum; i++)
        {
            cin >> point[i];
        }
        point[cityNum] = point[0];
        cityNum++;

        for (int i = 0; i < cityNum; i++)
        {
            for (int j = 0; j < cityNum; j++)
            {
                if (i == j)
                    arr[i][j] = 0;
                else
                    arr[i][j] = -1;
                path[i][j] = j;
            }
        }

        int flightNum;
        cin >> flightNum;
        for (int i = 0; i < flightNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            arr[from][to] = point[to];
        }

        for (int k = 0; k < cityNum; k++)
        {
            for (int i = 0; i < cityNum; i++)
            {
                for (int j = 0; j < cityNum; j++)
                {
                    if (arr[i][k] != -1 && arr[k][j] != -1)
                    {
                        if (arr[i][j] < arr[i][k] + arr[k][j])
                        {
                            arr[i][j] = arr[i][k] + arr[k][j];
                            path[i][j] = path[i][k];
                        }
                    }
                }
            }
        }

        cout << "CASE " << t << "#" << endl;
        cout << "points : " << arr[0][cityNum - 1] << endl;
        cout << "circuit : 1";
        int cntNode = 0;
        while (cntNode != cityNum - 1)
        {
            cout << "->";
            if (path[cntNode][cityNum - 1] == cityNum - 1)
                cout << 1;
            else
                cout << path[cntNode][cityNum - 1] + 1;
            cntNode = path[cntNode][cityNum - 1];
        }
        cout << endl;
        if (t < caseNum)
            cout << endl;
    }
    return 0;
}
