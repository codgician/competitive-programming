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

#define SIZE 100100

long long int arr[SIZE], tmp[SIZE];
long long int invNum;

void mergeArray(int leftPt, int midPt, int rightPt)
{
    int i = leftPt, j = midPt + 1;
    int tmpPt = 0;
    while (i <= midPt && j <= rightPt)
    {
        if (arr[i] <= arr[j])
        {
            tmp[tmpPt++] = arr[i++];
        }
        else
        {
            tmp[tmpPt++] = arr[j++];
            invNum += midPt - i + 1;
        }
    }

    while (i <= midPt)
    {
        tmp[tmpPt++] = arr[i++];
    }
    while (j <= rightPt)
    {
        tmp[tmpPt++] = arr[j++];
    }

    for (int t = leftPt; t <= rightPt; t++)
    {
        arr[t] = tmp[t - leftPt];
    }
}

void mergeSort(int leftPt, int rightPt)
{
    if (leftPt == rightPt)
        return;

    int midPt = leftPt + ((rightPt - leftPt) >> 1);
    mergeSort(leftPt, midPt);
    mergeSort(midPt + 1, rightPt);
    mergeArray(leftPt, midPt, rightPt);
}

int main()
{
    ios::sync_with_stdio(false);
    int num, x, y;
    while (scanf("%d%d%d", &num, &x, &y) != EOF)
    {
        invNum = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%lld", arr + i);
        }

        mergeSort(0, num - 1);

        long long int ans = invNum * min(x, y);
        printf("%lld\n", ans);
    }
    return 0;
}