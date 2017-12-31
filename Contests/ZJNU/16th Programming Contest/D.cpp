#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 100001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int buyNum, throwNum;
    cin >> buyNum >> throwNum;
    for (int i = 0; i < buyNum; i++)
    {
        cin >> arr[i];
    }
    sort(arr + 0, arr + buyNum);

    int repeatNum = 0;
    int typeNum = 1;
    for (int i = 1; i < buyNum; i++)
    {
        if (arr[i] == arr[i - 1])
            repeatNum++;
        else
            typeNum++;
    }
    if (repeatNum >= throwNum)
    {
        cout << typeNum << endl;
    }
    else
    {
        cout << typeNum - (throwNum - repeatNum) << endl;
    }
    return 0;
}
