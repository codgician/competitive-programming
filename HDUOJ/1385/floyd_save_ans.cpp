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
#define SIZE 999
#define INF 99999999
using namespace std;

int arr[SIZE][SIZE], path[SIZE][SIZE];
int tax[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int cityNum;
    while (cin >> cityNum)
    {
        if (cityNum == 0)
            break;

        for (int i = 0; i < cityNum; i++)
        {
            for (int j = 0; j < cityNum; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == -1)
                    arr[i][j] = INF;
                path[i][j] = j;
            }
        }

        for (int i = 0; i < cityNum; i++)
        {
            cin >> tax[i];
        }

        for (int k = 0; k < cityNum; k++)
        {
            for (int i = 0; i < cityNum; i++)
            {
                for (int j = 0; j < cityNum; j++)
                {
                    if (arr[i][k] != INF && arr[k][j] != INF)
                    {
                        if (arr[i][j] > arr[i][k] + arr[k][j] + tax[k])
                        {
                            arr[i][j] = arr[i][k] + arr[k][j] + tax[k];
                            path[i][j] = path[i][k];
                        }
                        else if (arr[i][j] == arr[i][k] + arr[k][j] + tax[k])
                        {
                            if (path[i][j] > path[i][k])
                                path[i][j] = path[i][k];
                        }
                    }
                }
            }
        }

        int from, to;
        while (cin >> from >> to)
        {
            if (from == -1 && to == -1)
                break;

            cout << "From " << from << " to " << to << " :" << endl;
            from--;
            to--;

            cout << "Path: " << from + 1;
            int cntNode = from;
            while (cntNode != to)
            {
                cout << "-->" << path[cntNode][to] + 1;
                cntNode = path[cntNode][to];
            }
            cout << endl;

            cout << "Total cost : " << arr[from][to] << endl << endl;
        }
    }
    return 0;
}
