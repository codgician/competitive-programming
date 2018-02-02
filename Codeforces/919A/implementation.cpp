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
#define SIZE 5001
using namespace std;

double arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int marketNum, appleNum;
    cin >> marketNum >> appleNum;
    for (int i = 0; i < marketNum; i++)
    {
        int price, weight;
        cin >> price >> weight;
        arr[i] = (double)price / weight;
    }
    sort(arr + 0, arr + marketNum);
    double ans = appleNum * arr[0];
    cout << fixed << setprecision(8) << ans << endl;
    return 0;
}
