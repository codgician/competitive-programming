#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define SIZE 1001

using namespace std;

int arr[SIZE][SIZE];
int leftNode[SIZE], rightNode[SIZE];

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
                    arr[i][j] = 0;
                else if (tmp == 'F')
                {
                    if (i == 0)
                        arr[i][j] = 1;
                    else
                        arr[i][j] = arr[i - 1][j] + 1;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < row; i++)
        {
            // Initialize.
            for (int j = 0; j < column; j++)
            {
                leftNode[j] = rightNode[j] = j;
            }

            // Find leftNode.
            for (int j = 1; j < column; j++)
            {
                while (arr[i][leftNode[j] - 1] >= arr[i][j] && leftNode[j] > 0)
                {
                    leftNode[j] = leftNode[leftNode[j] - 1];
                }
            }

            // Find rightNode.
            for (int j = column - 2; j >= 0; j--)
            {
                while (arr[i][rightNode[j] + 1] >= arr[i][j] && rightNode[j] < column - 1)
                {
                    rightNode[j] = rightNode[rightNode[j] + 1];
                }
            }

            for (int j = 0; j < column; j++)
            {
                ans = max(ans, (rightNode[j] - leftNode[j] + 1) * arr[i][j]);
            }
        }
        cout << ans * 3 << endl;
    }
    return 0;
}
