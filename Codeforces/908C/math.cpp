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

double diskX[SIZE];
double diskY[SIZE];

double getDistance(double ax, double ay, double bx, double by)
{
    return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
}

int main()
{
    ios::sync_with_stdio(false);
    int diskNum;
    double diskR;
    cin >> diskNum >> diskR;
    for (int i = 0; i < diskNum; i++)
    {
        cin >> diskX[i];
        diskY[i] = -1;
    }
    diskY[0] = diskR;

    for (int i = 1; i < diskNum; i++)
    {
        for (int j = 0; j < i; j++)
        {
            double delta = pow(2 * diskR, 2) - pow(diskX[i] - diskX[j], 2);
            if (delta < 0)
            {
                diskY[i] = max(diskY[i], diskR);
            }
            else
            {
                double cnt = diskY[j] + sqrt(pow(2 * diskR, 2) - pow(diskX[i] - diskX[j], 2));
                diskY[i] = max(diskY[i], cnt);
            }
        }
    }

    for (int i = 0; i < diskNum; i++)
    {
        cout << fixed << setprecision(10) << diskY[i];
        if (i < diskNum - 1)
            cout << " ";
        else
            cout << endl;
    }
    return 0;
}
