#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iomanip>
#define MAXN 2000000000
#define SIZE 6000
using namespace std;

long long int arr[SIZE];

long long int getPow(int a, int b)
{
    if (b == 0)
        return 1;
    long long int ans = a;
    for (int i = 1; i < b; i++)
        ans *= a;
    return ans;
}

void init()
{
    int cntPt = 0;
    for (int a = 0; getPow(2, a) <= MAXN; a++)
    {
        for (int b = 0; getPow(2, a) * getPow(3, b) <= MAXN; b++)
        {
            for (int c = 0; getPow(2, a) * getPow(3, b) * getPow(5, c) <= MAXN; c++)
            {
                for (int d = 0; getPow(2, a) * getPow(3, b) * getPow(5, c) * getPow(7, d) <= MAXN; d++)
                {
                    arr[cntPt] = getPow(2, a) * getPow(3, b) * getPow(5, c) * getPow(7, d);
                    cntPt++;
                }
            }
        }
    }
    sort(arr, arr + cntPt);
}

void print(int num)
{
    string fuck = "th";
    if (num % 100 != 11 && num % 10 == 1)
        fuck = "st";
    else if (num % 100 != 12 && num % 10 == 2)
        fuck = "nd";
    else if (num % 100 != 13 && num % 10 == 3)
        fuck = "rd";
    cout << "The " << num << fuck << " humble number is " << arr[num - 1] << "." << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int num;
    while (cin >> num)
    {
        if (num == 0)
            break;
        print(num);
    }
    return 0;
}
