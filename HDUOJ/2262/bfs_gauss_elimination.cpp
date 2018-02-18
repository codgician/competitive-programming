#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define MAP_SIZE 16
#define EQU_SIZE 256
using namespace std;

const double eps = 1e-10;

char arr[MAP_SIZE][MAP_SIZE];
bool hasVisited[MAP_SIZE][MAP_SIZE];
double equ[EQU_SIZE][EQU_SIZE], c[EQU_SIZE];
int id[MAP_SIZE][MAP_SIZE];
int dirx[4] = {1, -1, 0, 0}, diry[4] = {0, 0, 1, -1};
int row, column, equNum, varNum;

pair<int, int> startPt;

int getId(pair<int, int> cntPt)
{
    if (id[cntPt.first][cntPt.second] == -1)
        id[cntPt.first][cntPt.second] = varNum++;
    return id[cntPt.first][cntPt.second];
}

bool canMove(pair<int, int> cntPt)
{
    if (cntPt.first < 0 || cntPt.first >= row || cntPt.second < 0 || cntPt.second >= column || arr[cntPt.first][cntPt.second] == '#')
        return false;
    return true;
}

bool bfs()
{
    bool canArrive = false;
    memset(hasVisited, false, sizeof(hasVisited));
    memset(id, -1, sizeof(id));
    for (int i = 0; i < EQU_SIZE; i++)
    {
        for (int j = 0; j < EQU_SIZE; j++)
        {
            equ[i][j] = 0;
        }
    }

    queue<pair<int, int> > q;
    q.push(startPt);
    hasVisited[startPt.first][startPt.second] = true;
    id[startPt.first][startPt.second] = 0;
    equNum = 0;
    varNum = 1;

    while (!q.empty())
    {
        pair<int, int> cntPt = q.front();
        q.pop();

        if (arr[cntPt.first][cntPt.second] == '$')
        {
            canArrive = true;
            equ[equNum][getId(cntPt)] = 1;
            c[equNum] = 0;
            equNum++;
            continue;
        }

        equ[equNum][getId(cntPt)] = 1;
        int dirNum = 0;
        for (int i = 0; i < 4; i++)
        {
            pair<int, int> nextPt = make_pair(cntPt.first + dirx[i], cntPt.second + diry[i]);
            if (canMove(nextPt))
                dirNum++;
        }
        for (int i = 0; i < 4; i++)
        {
            pair<int, int> nextPt = make_pair(cntPt.first + dirx[i], cntPt.second + diry[i]);
            if (canMove(nextPt))
            {
                equ[equNum][getId(nextPt)] = -(1.0 / dirNum);
                if (!hasVisited[nextPt.first][nextPt.second])
                {
                    q.push(nextPt);
                    hasVisited[nextPt.first][nextPt.second] = true;
                }
            }
        }
        c[equNum] = 1;
        equNum++;
    }
    return canArrive;
}

int gauss()
{
    for (int cntRow = 0, cntColumn = 0; cntRow < equNum && cntColumn < varNum; cntRow++, cntColumn++)
    {
        int maxRow = cntRow;
        for(int i = cntRow + 1; i < equNum; i++)
        {
            if (fabs(equ[i][cntColumn]) > fabs(equ[maxRow][cntColumn]))
            {
                maxRow = i;
            }
        }
        if (fabs(equ[maxRow][cntColumn]) < eps)
        {
            return 0;
        }


        if(cntRow != maxRow)
        {
            for (int j = cntColumn; j < varNum; j++)
            {
                swap(equ[cntRow][j], equ[maxRow][j]);
            }
            swap(c[cntRow], c[maxRow]);
        }

        c[cntRow] /= equ[cntRow][cntColumn];

        for (int j = cntColumn + 1; j < varNum; j++)
        {
            equ[cntRow][j] /= equ[cntRow][cntColumn];
        }

        equ[cntRow][cntColumn] = 1;

        for(int i = 0; i < equNum; i++)
        {
            if(i != cntRow)
            {
                c[i] -= c[cntRow] * equ[i][cntColumn];
                for (int j = cntColumn + 1; j < varNum; j++)
                {
                    equ[i][j] -= equ[cntRow][j] * equ[i][cntColumn];
                }
                equ[i][cntColumn] = 0;
            }
        }
    }
    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == '@')
                    startPt = make_pair(i, j);
            }
        }
        if (!bfs())
        {
            cout << -1 << endl;
        }
        else
        {
            gauss();
            cout << fixed << setprecision(6) << c[getId(startPt)] << endl;
        }
    }
    return 0;
}
