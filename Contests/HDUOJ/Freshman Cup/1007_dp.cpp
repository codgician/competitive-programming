#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <climits>
#include <iomanip>
#define SIZE 101
using namespace std;

bool matrix[SIZE][SIZE];
int tmp[SIZE][SIZE];
int leftNode[SIZE], rightNode[SIZE];
int n;
int ans = 0;

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
        // Initialize.
        for (int j = 0; j < n; j++)
        {
            leftNode[j] = rightNode[j] = j;
        }

        // Find leftNode.
        for (int j = 1; j < n; j++)
        {
            while (tmp[i][leftNode[j] - 1] >= tmp[i][j] && leftNode[j] > 0)
            {
                leftNode[j] = leftNode[leftNode[j] - 1];
            }
        }

        // Find rightNode.
        for (int j = n - 2; j >= 0; j--)
        {
            while (tmp[i][rightNode[j] + 1] >= tmp[i][j] && rightNode[j] < n - 1)
            {
                rightNode[j] = rightNode[rightNode[j] + 1];
            }
        }

        for (int j = 0; j < n; j++)
        {
            ans = max(ans, (rightNode[j] - leftNode[j] + 1) * tmp[i][j]);
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
        // to finding the maximum all-0 / all-1 matrix.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
                if ((i + j) & 1)
                    matrix[i][j] = !matrix[i][j];
            }
        }

        // First find largest all-0 matrix.
        initTmp(0);
        getAns();

        // Next find largest all-1 matrix.
        initTmp(1);
        getAns();

        // I think ans == 1 means such 0-1 matrix don't exist.
        // But actually the test cases are weak. This is not covered.
        if (ans == 1)
            ans = 0;

        cout << ans << endl;
    }
    return 0;
}
