#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define SIZE 1002
using namespace std;

int arr[SIZE][SIZE];

void work(int a)
{
    arr[a][0] = arr[a - 1][0];
    for (int i = 1; i <= arr[a - 1][0]; i++)
    {
        arr[a][i] += arr[a - 1][i] + arr[a - 2][i] + arr[a - 4][i];
        if (arr[a][i] > 9)
        {
            arr[a][i + 1] += arr[a][i] / 10;
            arr[a][i] %= 10;
            if (i == arr[a - 1][0])
                arr[a][0]++;
        }
    }
}

void init()
{
    memset(arr, 0, sizeof(arr));
    // Length
    arr[1][0] = 1;
    arr[2][0] = 1;
    arr[3][0] = 1;
    arr[4][0] = 1;
    // Value
    arr[1][1] = 1;
    arr[2][1] = 2;
    arr[3][1] = 4;
    arr[4][1] = 7;
    for (int i = 5; i < SIZE; i++)
    {
        work(i);
    }
}

void print(int a)
{
    for (int i = arr[a][0]; i > 0; i--)
        cout << arr[a][i];
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int num;
    while (cin >> num)
    {
        print(num);
    }
    return 0;
}
