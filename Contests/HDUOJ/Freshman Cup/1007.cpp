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
int arr[SIZE][SIZE];
int leftNode[SIZE], rightNode[SIZE];
int n;

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
                if ((i + j) & 1)
                    matrix[i][j] = !matrix[i][j];
            }
        }

        // First find all-one matrix.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == false)
                    arr[i][j] = 0;
                else
                {
                    if (i == 0)
                        arr[i][j] = 1;
                    else
                        arr[i][j] = arr[i - 1][j] + 1;
                }

            }
        }

        int ans = 0;
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
                while (arr[i][leftNode[j] - 1] >= arr[i][j] && leftNode[j] > 0)
                {
                    leftNode[j] = leftNode[leftNode[j] - 1];
                }
            }

            // Find rightNode.
            for (int j = n - 2; j >= 0; j--)
            {
                while (arr[i][rightNode[j] + 1] >= arr[i][j] && rightNode[j] < n - 1)
                {
                    rightNode[j] = rightNode[rightNode[j] + 1];
                }
            }

            for (int j = 0; j < n; j++)
            {
                ans = max(ans, (rightNode[j] - leftNode[j] + 1) * arr[i][j]);
            }
        }


        // Then find all-zero matrix.
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == true)
                    arr[i][j] = 0;
                else
                {
                    if (i == 0)
                        arr[i][j] = 1;
                    else
                        arr[i][j] = arr[i - 1][j] + 1;
                }

            }
        }

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
                while (arr[i][leftNode[j] - 1] >= arr[i][j] && leftNode[j] > 0)
                {
                    leftNode[j] = leftNode[leftNode[j] - 1];
                }
            }

            // Find rightNode.
            for (int j = n - 2; j >= 0; j--)
            {
                while (arr[i][rightNode[j] + 1] >= arr[i][j] && rightNode[j] < n - 1)
                {
                    rightNode[j] = rightNode[rightNode[j] + 1];
                }
            }

            for (int j = 0; j < n; j++)
            {
                ans = max(ans, (rightNode[j] - leftNode[j] + 1) * arr[i][j]);
            }
        }

        cout << ans << endl;

    }
    return 0;
}

