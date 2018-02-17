#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 1001
using namespace std;

const double eps = 1e-10;

typedef struct _Node
{
    double stayProb;
    double columnProb;
    double rowProb;
    double expect;
} Node;

Node arr[SIZE][SIZE];

int main()
{
    int row, column;
    while (scanf("%d%d", &row, &column) != EOF)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                scanf("%lf%lf%lf", &arr[i][j].stayProb, &arr[i][j].columnProb, &arr[i][j].rowProb);
                arr[i][j].expect = 0;
            }
        }

        for (int i = row - 1; i >= 0; i--)
        {
            for (int j = column - 1; j >= 0; j--)
            {
                if (i == row - 1 && j == column - 1)
                    continue;
                if (fabs(1 - arr[i][j].stayProb) < eps)
                    continue;

                if (i < row - 1)
                    arr[i][j].expect += arr[i][j].rowProb * arr[i + 1][j].expect;
                if (j < column - 1)
                    arr[i][j].expect += arr[i][j].columnProb * arr[i][j + 1].expect;

                arr[i][j].expect += 2.0;
                arr[i][j].expect /= (1.0 - arr[i][j].stayProb);
            }
        }

        printf("%.3lf\n", arr[0][0].expect);
    }
    return 0;
}
