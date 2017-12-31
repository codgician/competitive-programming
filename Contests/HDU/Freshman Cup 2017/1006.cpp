#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <climits>
#include <iomanip>
#define SIZE 50010
using namespace std;

typedef struct Node {
    int prev;
    int nxt;
} page;

page arr[SIZE], tmp[SIZE];

int ans = 0;

void mergeArray(int headPt, int medPt, int tailPt)
{
    int i = headPt, j = medPt + 1;
    int tmpPt = 0;
    while (i <= medPt && j <= tailPt)
    {
        if (arr[i].prev <= arr[j].prev)
        {
            tmp[tmpPt++] = arr[i++];
        }
        else
        {
            tmp[tmpPt++] = arr[j++];
            ans += medPt - i + 1;
        }
    }

    while (i <= medPt)
    {
        tmp[tmpPt++] = arr[i++];
    }
    while (j <= tailPt)
    {
        tmp[tmpPt++] = arr[j++];
    }

    for (int t = headPt; t <= tailPt; t++)
    {
        arr[t] = tmp[t - headPt];
    }
}

void mergeSort(int headPt, int tailPt)
{
    if (headPt == tailPt)
        return;

    int medPt = headPt + (tailPt - headPt) / 2;
    mergeSort(headPt, medPt);
    mergeSort(medPt + 1, tailPt);
    mergeArray(headPt, medPt, tailPt);
}


int main()
{
    ios::sync_with_stdio(false);
    int pageNum;
    while (cin >> pageNum)
    {
        int paperNum = pageNum / 2;
        ans = 0;
        for (int i = 0; i < paperNum; i++)
        {
            cin >> arr[i].prev >> arr[i].nxt;
            if (arr[i].prev > arr[i].nxt)
            {
                swap(arr[i].prev, arr[i].nxt);
                ans++;
            }
        }

        mergeSort(0, paperNum - 1);

        cout << ans << endl;
    }
    return 0;
}
