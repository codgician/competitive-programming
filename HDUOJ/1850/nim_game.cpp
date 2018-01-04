#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int cardPile;
    while (cin >> cardPile)
    {
        if (cardPile == 0)
            break;

        int ans = 0;
        for (int i = 0; i < cardPile; i++)
        {
            cin >> arr[i];
            ans ^= arr[i];
        }

        int tmp = 0, num = 0;
        for (int i = 0; i < cardPile; i++)
        {
            tmp = ans ^ arr[i];
            if (tmp < arr[i])
                num++;
        }
        cout << num << endl;
    }
    return 0;
}
