#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <climits>
#define SIZE 1001
using namespace std;

typedef struct Node {
    int height;
    int startPos;
} rec;

rec arr[SIZE];

int matrix[SIZE][SIZE];

int arrPt = 0;

void push(int height, int startPos)
{
    arr[arrPt].height = height;
    arr[arrPt].startPos = startPos;
    arrPt++;
}

void pop()
{
    arrPt--;
}

rec getHead()
{
    return arr[arrPt - 1];
}

int getLength()
{
    return arrPt;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int row, column;
        cin >> row >> column;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                char tmp;
                cin >> tmp;
                if (tmp == 'R')
                {
                    matrix[i][j] = 0;
                }
                else
                {
                    if (i == 0)
                        matrix[i][j] = 1;
                    else
                        matrix[i][j] = matrix[i - 1][j] + 1;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < row; i++)
        {
            arrPt = 0;
            // Refrain from considering empty stack situation.
            push(-1, 0);

            for (int j = 0; j < column; j++)
            {
                int startPos = j;

                while (getHead().height > matrix[i][j])
                {
                    ans = max(ans, (j - getHead().startPos) * getHead().height);
                    startPos = getHead().startPos;
                    pop();
                }

                push(matrix[i][j], startPos);

            }

            while (getLength() > 1)
            {
                ans = max(ans, (column - getHead().startPos) * getHead().height);
                pop();
            }
        }
        cout << ans * 3 << endl;
    }
    return 0;
}
