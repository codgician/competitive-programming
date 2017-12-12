#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
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
        int giftNum, bagSize;
        cin >> giftNum >> bagSize;
        for (int i = 0; i < giftNum; i++)
        {
            int giftSize, like;
            cin >> giftSize >> like;
            arr[i] = giftSize - like;
        }

        sort(arr + 0, arr + giftNum);

        int cntSize = 0;
        bool canPut = true;
        for (int i = 0; i < giftNum; i++)
        {
            cntSize += arr[i];
            if (cntSize > bagSize)
            {
                canPut = false;
                break;
            }
        }

        if (canPut)
        {
            cout << "yes" << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }
    return 0;
}
