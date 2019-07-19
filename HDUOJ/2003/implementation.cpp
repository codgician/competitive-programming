#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
    double a;
    while (scanf("%lf", &a) != EOF)
        printf("%.2lf\n", abs(a));
    return 0;
}