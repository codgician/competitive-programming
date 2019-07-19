#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define SIZE 1001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int arrSize;
        cin >> arrSize;
        for (int i = 0; i < arrSize; i++)
        {
            cin >> arr[i];
        }
        sort(arr, arr + arrSize);
        for (int i = 0; i < arrSize; i++)
        {
            cout << arr[i];
            if (i == arrSize - 1)
                cout << endl;
            else
                cout << " ";
        }
    }
    return 0;
}
