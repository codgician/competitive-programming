#include <iostream>
#include <cstdio>
#define SIZE 21
using namespace std;

long long int arr[SIZE];

void init()
{
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 1;
    for (int i = 3; i < SIZE; i++)
        arr[i] = (i - 1) * (arr[i - 1] + arr[i - 2]);
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
