#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 51
using namespace std;

typedef struct _Point {
    int i;
    int j;
} point;

int di[24][4] = {1, -1, 0, 0, 1, -1, 0, 0, 1, 0, -1, 0, 1, 0, 0, -1, 1, 0, -1, 0, 1, 0, 0, -1, -1, 1, 0, 0, -1, 1, 0, 0, -1, 0, 1, 0, -1, 0, 0, 1, -1, 0, 1, 0, -1, 0, 0, 1, 0, 1, -1, 0, 0, 1, 0, -1, 0, -1, 1, 0, 0, -1, 0, 1, 0, 0, 1, -1, 0, 0, -1, 1, 0, 1, -1, 0, 0, 1, 0, -1, 0, -1, 1, 0, 0, -1, 0, 1, 0, 0, 1, -1, 0, 0, -1, 1};
int dj[24][4] = {0, 0, 1, -1, 0, 0, -1, 1, 0, 1, 0, -1, 0, 1, -1, 0, 0, -1, 0, 1, 0, -1, 1, 0, 0, 0, 1, -1, 0, 0, -1, 1, 0, 1, 0, -1, 0, 1, -1, 0, 0, -1, 0, 1, 0, -1, 1, 0, 1, 0, 0, -1, 1, 0, -1, 0, 1, 0, 0, -1, 1, 0, -1, 0, 1, -1, 0, 0, 1, -1, 0, 0, -1, 0, 0, 1, -1, 0, 1, 0, -1, 0, 0, 1, -1, 0, 1, 0, -1, 1, 0, 0, -1, 1, 0, 0};

bool arr[SIZE][SIZE]; // has obstacle
point startPt, endPt;
int row, column;

bool canMove(int i, int j)
{
    if (i < 0 || i >= row || j < 0 || j >= column || arr[i][j])
        return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> row >> column;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            char ch;
            cin >> ch;
            if (ch == '.')
            {
                arr[i][j] = false;
            }
            else if (ch == '#')
            {
                arr[i][j] = true;
            }
            else if (ch == 'S')
            {
                startPt.i = i;
                startPt.j = j;
                arr[i][j] = false;
            }
            else if (ch == 'E')
            {
                endPt.i = i;
                endPt.j = j;
                arr[i][j] = false;
            }
        }
    }
    string dir;
    cin >> dir;

    int ans = 0;
    for (int i = 0; i < 24; i++)
    {
        point cntPt = startPt;
        for (int j = 0; j < dir.length(); j++)
        {
            int cnt = dir[j] - '0';
            cntPt.i += di[i][cnt];
            cntPt.j += dj[i][cnt];
            if (!canMove(cntPt.i, cntPt.j))
            {
                break;
            }
            if (cntPt.i == endPt.i && cntPt.j == endPt.j)
            {
                ans++;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
