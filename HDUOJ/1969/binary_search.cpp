#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define PI acos(-1.0)
#define SIZE 10001
using namespace std;

double arr[SIZE];
int pieNum, friendNum;

bool canSatisfyNeed(double pieceSize)
{
    int sum = 0;
    for (int i = 0; i < pieNum; i++)
    {
        sum += (int)(arr[i] / pieceSize);
    }
    if (sum < friendNum + 1)
        return false;
    else
        return true;
}

double work(double left, double right)
{
    double mid = (left + right) / 2;

    if (right - left < 1e-6)
        return mid;

    if (canSatisfyNeed(mid))
        return work(mid, right);
    else
        return work(left, mid);
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        cin >> pieNum >> friendNum;
        double maxSize = -1, sizeSum = 0;
        for (int i = 0; i < pieNum; i++)
        {
            int r;
            cin >> r;
            arr[i] = PI * r * r;
            sizeSum += arr[i];
        }
        cout << fixed << setprecision(4) << work(0, sizeSum / (friendNum + 1)) << endl;
    }
    return 0;
}
