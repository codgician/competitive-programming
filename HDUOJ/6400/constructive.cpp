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

#define SIZE 210

char arr[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int row, column;
        cin >> row >> column;

        if ((row & 1) && (column & 1))
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    cout << "(";
                }
                cout << endl;
            }
            continue;
        }

        if ((row & 1) || (column & 1))
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    if (row & 1)
                        cout << ((j & 1) ? ")" : "(");
                    else
                        cout << ((i & 1) ? ")" : "(");
                }
                cout << endl;
            }
            continue;
        }


        bool hasSwapped = false;
        if (row < column)
        {
            swap(row, column);
            hasSwapped = true;
        }

        int ans1 = row + ((column - 2) >> 1);
        int ans2 = row + column - 4;

        if (ans1 >= ans2)
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    if (i & 1)
                    {
                        if (j == 0)
                            arr[i][j] = '(';
                        else if (j == column - 1)
                            arr[i][j] = ')';
                        else
                            arr[i][j] = ((j & 1) ? '(' : ')');
                    }
                    else
                    {
                        arr[i][j] = ((j & 1) ? ')' : '(');
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < row; i++)
            {
                if (i == 0)
                {
                    for (int j = 0; j < column; j++)
                    {
                        arr[i][j] = '(';
                    }
                    continue;
                }
                else if (i == row - 1)
                {
                    for (int j = 0; j < column; j++)
                    {
                        arr[i][j] = ')';
                    }
                    continue;
                }

                for (int j = 0; j < column; j++)
                {
                    if (j == 0)
                        arr[i][j] = '(';
                    else if (j == column - 1)
                        arr[i][j] = ')';
                    else
                        arr[i][j] = (!((i + j) & 1) ? '(' : ')');
                }
            }
        }

        if (hasSwapped)
        {
            for (int j = 0; j < column; j++)
            {
                for (int i = 0; i < row; i++)
                {
                    cout << arr[i][j];
                }
                cout << endl;
            }
        }
        else
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    cout << arr[i][j];
                }
                cout << endl;
            }
        }
    }
    return 0;
}