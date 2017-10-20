#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define SIZE 101
using namespace std;

typedef struct Node {
    int price;
    int space;
} itm;

itm arr[SIZE];

bool cmpRule(itm a, itm b)
{
    return a.price > b.price;
}

int main()
{
    ios::sync_with_stdio(false);
    int bagSize, itemNum;
    while (cin >> bagSize)
    {
        if (bagSize == 0)
            break;
        cin >> itemNum;
        for (int i = 0; i < itemNum; i++)
        {
            cin >> arr[i].price >> arr[i].space;
        }
        sort(arr, arr + itemNum, cmpRule);
        int ans = 0;
        for (int i = 0; i < itemNum; i++)
        {

            if (bagSize > arr[i].space)
            {
                ans += arr[i].space * arr[i].price;
                bagSize -= arr[i].space;
            }
            else
            {
                ans += bagSize * arr[i].price;
                bagSize = 0;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
