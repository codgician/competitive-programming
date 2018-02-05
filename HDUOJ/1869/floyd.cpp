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
#define INF 20001
using namespace std;

int arr[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int peopleNum, relationNum;
    while (cin >> peopleNum >> relationNum)
    {
        for (int i = 0; i < peopleNum; i++)
        {
            for (int j = 0; j < peopleNum; j++)
            {
                if (i == j)
                    arr[i][j] = 0;
                else
                    arr[i][j] = INF;
            }
        }

        for (int i = 0; i < relationNum; i++)
        {
            int a, b, len;
            cin >> a >> b;
            arr[a][b] = 1;
            arr[b][a] = 1;
        }

        for (int k = 0; k < peopleNum; k++)
        {
            for (int i = 0; i < peopleNum; i++)
            {
                for (int j = 0; j < peopleNum; j++)
                {
                    arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
                }
            }
        }

        bool ans = true;
        for (int i = 0; i < peopleNum; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[i][j] > 7)
                {
                    ans = false;
                    break;
                }
            }
        }

        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
