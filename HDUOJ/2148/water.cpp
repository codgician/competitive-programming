#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#define SIZE 1001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int stuNum, lelePt;
        cin >> stuNum >> lelePt;
        lelePt--;
        for (int i = 0; i < stuNum; i++)
        {
            cin >> arr[i];
        }
        int ans = 0;
        for (int i = 0; i < stuNum; i++)
        {
            if (arr[i] > arr[lelePt])
                ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
