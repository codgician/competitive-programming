#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 1001
using namespace std;

bool isFibo[SIZE];
int fibo[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(isFibo, false, sizeof(isFibo));
    fibo[0] = 1;
    fibo[1] = 1;
    isFibo[0] = true;
    for (int i = 2; fibo[i - 1] <= 1000; i++)
    {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        isFibo[fibo[i] - 1] = true;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        if (isFibo[i])
            cout << "O";
        else
            cout << "o";
    }
    cout << endl;
    return 0;
}
