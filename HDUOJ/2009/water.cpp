#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    double a;
    int num;
    while (cin >> a >> num)
    {
        double cnt = a, sum = a;
        for (int i = 0; i < num - 1; i++)
        {
            cnt = sqrt(cnt);
            sum += cnt;
        }
        printf("%.2f\n", sum);
    }
    return 0;
}
