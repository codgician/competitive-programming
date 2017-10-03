#include <cstdio>
#include <cmath>
#define PI 3.1415927
using namespace std;

int main()
{
    double r, ans;
    while (scanf("%lf", &r) != EOF)
    {
        ans = pow(r, 3) / 3 * 4 * PI;
        printf("%.3lf\n", ans);
    }
    return 0;
}