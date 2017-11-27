#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <climits>
#include <iomanip>
#define SIZE 110
using namespace std;

typedef struct Node {
    int height;
    int startPos;
} rec;

rec arr[SIZE];

bool matrix[SIZE][SIZE];
int tmp[SIZE][SIZE];
int n, ans = 0;

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

void initTmp(bool type)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == type)
            {
                if (i == 0)
                {
                    tmp[i][j] = 1;
                }
                else
                {
                    tmp[i][j] = tmp[i - 1][j] + 1;
                }
            }
            else
            {
                tmp[i][j] = 0;
            }
        }
    }
}

void getAns()
{
    for (int i = 0; i < n; i++)
    {
        arrPt = 0;
        // Refrain from considering empty stack situation.
        push(-1, 0);

        for (int j = 0; j < n; j++)
        {
            int startPos = j;

            while (getHead().height > tmp[i][j])
            {
                ans = max(ans, (j - getHead().startPos) * getHead().height);
                startPos = getHead().startPos;
                pop();
            }

            push(tmp[i][j], startPos);

        }

        while (getLength() > 1)
        {
            ans = max(ans, (n - getHead().startPos) * getHead().height);
            pop();
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        ans = 0;
        cin >> n;

        // Convert the problem from finding the maximum 0-1 matrix
        // to finding the maximum all 0 / all 1 matrix.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
                if ((i + j) & 1)
                    matrix[i][j] = !matrix[i][j];
            }
        }

        // First find biggest all-0 matrix.
        initTmp(0);
        getAns();

        // Next find biggest all-1 matrix.
        initTmp(1);
        getAns();

        if (ans == 1)
            ans = 0;

        cout << ans << endl;
    }
    return 0;
}

