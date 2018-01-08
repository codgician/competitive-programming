#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#define SIZE 41
using namespace std;

int arr[SIZE];

void init()
{
    arr[0] = 3;
    arr[1] = 9;
    for (int i = 2; i < SIZE; i++)
    {
        arr[i] = (arr[i - 1] << 1) + arr[i - 2];
    }
}

int main()
{
    init();
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int cnt;
        cin >> cnt;
        cout << arr[cnt - 1] << endl;
    }
    return 0;
}
