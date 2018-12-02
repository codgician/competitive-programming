#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8
#define SIZE 1001
using namespace std;

bool arr[SIZE][SIZE]; // is star?
int ans[SIZE][SIZE];

int main()
{
    int row, column, queryNum;
    scanf("%d%d%d", &row, &column, &queryNum);
    getchar();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            char ch;
            scanf("%c", &ch);
            if (ch == '*')
            {
                arr[i][j] = true;
            }
            else if (ch == '#')
            {
                arr[i][j] = false;
            }
            ans[i][j] = 15;
        }
        getchar();
    }

    for (int cnti = 0; cnti < row; cnti++)
    {
        for (int cntj = 0; cntj < column; cntj++)
        {
            if (!arr[cnti][cntj])
            {
                // Left brain has nothing right
                for (int j = cntj - 1; j >= 0; j--)
                {
                    if (!arr[cnti][j])
                        break;
                    if ((ans[cnti][j] & RIGHT) > 0)
                        ans[cnti][j] -= RIGHT;
                }
                // Right brain has nothing left
                for (int j = cntj + 1; j < column; j++)
                {
                    if (!arr[cnti][j])
                        break;
                    if ((ans[cnti][j] & LEFT) > 0)
                        ans[cnti][j] -= LEFT;
                }
                // Up brain has nothing down
                for (int i = cnti - 1; i >= 0; i--)
                {
                    if (!arr[i][cntj])
                        break;
                    if ((ans[i][cntj] & DOWN) > 0)
                        ans[i][cntj] -= DOWN;
                }
                // Down brain has nothing up
                for (int i = cnti + 1; i < row; i++)
                {
                    if (!arr[i][cntj])
                        break;
                    if ((ans[i][cntj] & UP) > 0)
                        ans[i][cntj] -= UP;
                }
            }
        }
    }

    while (queryNum--)
    {
        int cnti, cntj;
        char ch;
        bool flag = true;
        scanf("%d%d", &cnti, &cntj);
        getchar();
        scanf("%c", &ch);
        getchar();
        cnti--;
        cntj--;
        int dir;
        if (ch == 'U')
            dir = UP;
        else if (ch == 'D')
            dir = DOWN;
        else if (ch == 'L')
            dir = LEFT;
        else if (ch == 'R')
            dir = RIGHT;
        if ((ans[cnti][cntj] & dir) > 0)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
