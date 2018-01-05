#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <string>
#include <climits>
#include <iomanip>
#define IS_N true
#define IS_P false
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long int n;
    while (cin >> n)
    {
        long long int cnt = 9;
        bool flag = IS_N;
        while (cnt < n)
        {
            if (flag == IS_N)
            {
                cnt *= 2;
                flag = IS_P;
            }
            else
            {
                cnt *= 9;
                flag = IS_N;
            }
        }
        if (flag == IS_N)
        {
            cout << "Stan wins." << endl;
        }
        else
        {
            cout << "Ollie wins." << endl;
        }
    }
    return 0;
}
