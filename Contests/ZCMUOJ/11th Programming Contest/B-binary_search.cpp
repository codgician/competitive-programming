#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 1357210
using namespace std;

unsigned long long int arr[SIZE];
int arrPt;

void init()
{
    for (unsigned long long int i = 0; i < SIZE; i++)
    {
        arr[i] = ((i * i * i) << 2) + (i << 1);
    }
}

int work(int leftPt, int rightPt, unsigned long long int n)
{
    int midPt = (leftPt + rightPt) / 2;

    if (arr[midPt] >= n && arr[midPt - 1] < n)
        return midPt;

    if (arr[midPt] < n)
    {
        return work(midPt + 1, rightPt, n);
    }
    else
    {
        return work(leftPt, midPt - 1, n);
    }
}

int main()
{
    init();
    int caseNum;
    scanf("%d", &caseNum);
    for (int t = 0; t < caseNum; t++)
    {
        unsigned long long int n;
        scanf("%llu", &n);
        // int pt = lower_bound(arr + 0, arr + SIZE, n) - arr;
        int pt = work(0, SIZE - 1, n);
        printf("%llu\n", arr[pt]);
    }
    return 0;
}
