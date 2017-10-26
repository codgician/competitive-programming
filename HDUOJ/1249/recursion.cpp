#include <iostream>
#include <cstdio>
#define SIZE 10001
using namespace std;

int arr[SIZE];

void init()
{
    arr[1] = 2;
    for (int i = 2; i < SIZE; i++)
        arr[i] = arr[i - 1] + 6 * (i - 1);
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
