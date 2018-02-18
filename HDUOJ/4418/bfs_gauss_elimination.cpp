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
#define SIZE 210
using namespace std;

const double eps = 1e-10;

double equ[SIZE][SIZE], c[SIZE], prob[SIZE];
bool hasVisited[SIZE];
int id[SIZE];

int len, maxStep, startPt, endPt, dir, equNum, varNum;
double cons;

int getId(int cntPt)
{
    if (id[cntPt] == -1)
        id[cntPt] = varNum++;
    return id[cntPt];
}

bool bfs()
{
    memset(hasVisited, false, sizeof(hasVisited));
    memset(id, -1, sizeof(id));
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            equ[i][j] = 0;
        }
        c[i] = 0;
    }

    queue<int> q;
    q.push(startPt);
    id[startPt] = 0;
    hasVisited[startPt] = true;
    equNum = 0;
    varNum = 1;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        if (cntPt == endPt || cntPt == len - endPt)
        {
            equ[equNum][getId(cntPt)] = 1;
            c[equNum] = 0;

            for (int i = 1; i <= maxStep; i++)
            {
                if (!hasVisited[(cntPt + i) % len] && fabs(prob[i]) > eps)
                {
                    hasVisited[(cntPt + i) % len] = true;
                    q.push((cntPt + i) % len);
                }
            }
            equNum++;
            continue;
        }

        equ[equNum][getId(cntPt)] = 1;
        for (int i = 1; i <= maxStep; i++)
        {
            if (!hasVisited[(cntPt + i) % len] && fabs(prob[i]) > eps)
            {
                hasVisited[(cntPt + i) % len] = true;
                q.push((cntPt + i) % len);
            }

            // (cntPt + i) % len might be identical for different i
            if (fabs(prob[i]) > eps)
                equ[equNum][getId((cntPt + i) % len)] -= prob[i];
        }
        c[equNum] = cons;
        equNum++;
    }

    if (!hasVisited[endPt] && !hasVisited[len - endPt])
        return false;
    else
        return true;
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
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cons = 0.0;
        cin >> len >> maxStep >> endPt >> startPt >> dir;
        for (int i = 1; i <= maxStep; i++)
        {
            cin >> prob[i];
            prob[i] /= 100;
            cons += i * prob[i];
        }

        if (startPt == endPt)
        {
            cout << "0.00" << endl;
            continue;
        }

        len = (len - 1) * 2;
        if (dir == 1)
            startPt = len - startPt;


        if (!bfs())
        {
            cout << "Impossible !" << endl;
        }
        else
        {
            gauss();
            cout << fixed << setprecision(2) << c[getId(startPt)] << endl;
        }
    }
    return 0;
}
