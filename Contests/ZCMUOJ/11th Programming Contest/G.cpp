#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    for (int t = 0; t < caseNum; t++)
    {
        double prev, cnt;
        scanf("%lf%lf", &prev, &cnt);
        printf("%.0lf\n", cnt - prev);
    }
    return 0;
}
