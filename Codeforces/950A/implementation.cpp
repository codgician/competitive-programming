#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int leftNum, rightNum, bothNum;
    cin >> leftNum >> rightNum >> bothNum;
    int biggerNum = max(leftNum, rightNum);
    int smallerNum = min(leftNum, rightNum);
    int delta = biggerNum - smallerNum;

    int ans;
    if (delta >= bothNum)
    {
        ans =  smallerNum + bothNum;
    }
    else
    {
        ans = biggerNum + (bothNum - delta) / 2;
    }

    cout << ans * 2 << endl;
    return 0;
}
