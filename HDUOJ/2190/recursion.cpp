#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define SIZE 31
using namespace std;

int arr[SIZE];

void init()
{
    arr[1] = 1;
    arr[2] = 3;
    for (int i = 3; i < SIZE; i++)
        arr[i] = arr[i - 1] + 2 * arr[i - 2];
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int tmp;
        cin >> tmp;
        cout << arr[tmp] << endl;
    }
    return 0;
}
