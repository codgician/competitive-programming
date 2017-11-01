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
    int twoPt = 0, threePt = 0, fivePt = 0, sevenPt = 0;
    arr[0] = 1;
    for (int i = 1; i < 5842; i++)
    {
        long long int twoNext = arr[twoPt] * 2;
        long long int threeNext = arr[threePt] * 3;
        long long int fiveNext = arr[fivePt] * 5;
        long long int sevenNext = arr[sevenPt] * 7;

        arr[i] = min(min(twoNext, threeNext), min(fiveNext, sevenNext));

        if (arr[i] == twoNext)
            twoPt++;
        if (arr[i] == threeNext)
            threePt++;
        if (arr[i] == fiveNext)
            fivePt++;
        if (arr[i] == sevenNext)
            sevenPt++;
    }
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
