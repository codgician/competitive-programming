#include <iostream>
#include <cstdio>
#define SIZE 1001
using namespace std;

int arr[SIZE];

void init()
{
    arr[1] = 2;
    for (int i = 2; i < SIZE; i++)
        arr[i] = arr[i - 1] + (i - 1) * i / 2 + 1;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int n;
    while (cin >> n)
        cout << arr[n] << endl;
    return 0;
}
