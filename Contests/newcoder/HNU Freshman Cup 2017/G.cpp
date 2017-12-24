#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 1000001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int sockNum;
        cin >> sockNum;
        for (int i = 0; i < sockNum; i++)
            cin >> arr[i];
        sort(arr + 0, arr + sockNum);
        cout << arr[0] + arr[1] << endl;
     }
    return 0;
}
