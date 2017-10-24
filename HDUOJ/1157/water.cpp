#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define SIZE 10001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int cowNum;
    while (cin >> cowNum)
    {
        for (int t = 0; t < cowNum; t++)
            cin >> arr[t];
        sort(arr, arr + cowNum);
        cout << arr[(cowNum - 1) / 2] << endl;
    }
    return 0;
}
