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
#define MATCH_SIZE 51
using namespace std;

bool isPond[SIZE][SIZE], hasTried[MATCH_SIZE];
int arr[MATCH_SIZE][MATCH_SIZE], partnerMatch[MATCH_SIZE];
int dir[2][2] = {1, 0, 0, 1};
int row, column;

map<int, pair<int, int> > origId;
map<pair<int, int>, int> newId;

int cntId = 0;

int getId(int x, int y)
{
    pair<int, int> p = make_pair(x, y);
    if (!newId.count(p))
    {
        newId[p] = cntId;
        origId[cntId] = p;
        cntId++;
    }
    return newId[p];
}

bool canFind(int blockId)
{
    for (int i = 0; i < cntId; i++)
    {
        if (arr[blockId][i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (partnerMatch[i] == -1 || canFind(partnerMatch[i]))
            {
                partnerMatch[i] = blockId;
                return true;
            }
        }
    }
    return false;
}

int hungarain()
{
    memset(partnerMatch, -1, sizeof(partnerMatch));
    int ans = 0;
    for (int i = 0; i < cntId; i++)
    {
        memset(hasTried, false, sizeof(hasTried));
        if (canFind(i))
            ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column)
    {
        if (row == 0 && column == 0)
            break;

        origId.clear();
        newId.clear();
        cntId = 0;

        int pondNum;
        cin >> pondNum;

        memset(isPond, false, sizeof(isPond));
        for (int i = 0; i < pondNum; i++)
        {
            int x, y;
            cin >> x >> y;
            isPond[--x][--y] = true;
        }

        memset(arr, false, sizeof(arr));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (isPond[i][j])
                    continue;

                for (int k = 0; k < 2; k++)
                {
                    int nexti = i + dir[0][k];
                    int nextj = j + dir[1][k];

                    if (nexti >= 0 && nexti < row && nextj >= 0 && nextj < column && !isPond[nexti][nextj])
                    {
                        if ((i + j) & 1)
                        {
                            arr[getId(i, j)][getId(nexti, nextj)] = true;
                        }
                        else
                        {
                            arr[getId(nexti, nextj)][getId(i, j)] = true;
                        }
                    }
                }
            }
        }

        int ans = hungarain();
        cout << ans << endl;
        for (int i = 0; i < cntId; i++)
        {
            if (partnerMatch[i] != -1)
            {
                cout << "(" << origId[partnerMatch[i]].first + 1 << "," << origId[partnerMatch[i]].second + 1 << ")--(" << origId[i].first + 1 << "," << origId[i].second + 1 << ")" << endl;
            }
        }
    }
    return 0;
}
