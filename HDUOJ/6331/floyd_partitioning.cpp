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

#define BLOCK_SIZE 101
#define SIZE 55

int arr[SIZE][SIZE], dis[SIZE][SIZE], tmp[SIZE][SIZE];
int fstArr[BLOCK_SIZE][SIZE][SIZE], sndArr[BLOCK_SIZE][SIZE][SIZE];
int vertexNum, edgeNum;

inline void multiply(int fst[][SIZE], int snd[][SIZE], int ans[][SIZE])
{
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            ans[i][j] = INT_MAX;
            for (int k = 0; k < vertexNum; k++)
            {
                if (fst[i][k] != INT_MAX && snd[k][j] != INT_MAX)
                    ans[i][j] = min(ans[i][j], fst[i][k] + snd[k][j]);
            }
        }
    }
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        scanf("%d%d", &vertexNum, &edgeNum);
        for (int i = 0; i < vertexNum; i++)
        {
            for (int j = 0; j < vertexNum; j++)
            {
                // i == j is not zero cuz such edge does not exist!
                arr[i][j] = INT_MAX;
                dis[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, len;
            scanf("%d%d%d", &from, &to, &len);
            from--;
            to--;
            arr[from][to] = min(arr[from][to], len);
            dis[from][to] = arr[from][to];
        }

        for (int i = 0; i < vertexNum; i++)
        {
            for (int j = 0; j < vertexNum; j++)
            {
                fstArr[0][i][j] = (i == j) ? 0 : INT_MAX;
                sndArr[0][i][j] = (i == j) ? 0 : INT_MAX;
            }
        }
        for (int i = 1; i < BLOCK_SIZE; i++)
        {
            multiply(sndArr[i - 1], arr, sndArr[i]);
        }
        for (int i = 1; i < BLOCK_SIZE; i++)
        {
            multiply(fstArr[i - 1], sndArr[100], fstArr[i]);
        }

        // Floyd
        for (int k = 0; k < vertexNum; k++)
        {
            for (int i = 0; i < vertexNum; i++)
            {
                for (int j = 0; j < vertexNum; j++)
                {
                    if (dis[i][k] != INT_MAX && dis[k][j] != INT_MAX)
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }

        for (int t = 0; t < BLOCK_SIZE; t++)
        {
            multiply(fstArr[t], dis, tmp);
            for (int i = 0; i < vertexNum; i++)
            {
                for (int j = 0; j < vertexNum; j++)
                {
                    fstArr[t][i][j] = tmp[i][j];
                }
            }
        }

        int qNum;
        scanf("%d", &qNum);
        while (qNum--)
        {
            int from, to, edgeNum;
            scanf("%d%d%d", &from, &to, &edgeNum);
            from--;
            to--;

            int fstNum = edgeNum / 100, sndNum = edgeNum % 100;
            int ans = INT_MAX;
            for (int i = 0; i < vertexNum; i++)
            {
                if (fstArr[fstNum][from][i] != INT_MAX && sndArr[sndNum][i][to] != INT_MAX)
                    ans = min(ans, fstArr[fstNum][from][i] + sndArr[sndNum][i][to]);
            }

            if (ans == INT_MAX)
                puts("-1");
            else
                printf("%d\n", ans);
        }
    }
    return 0;
}