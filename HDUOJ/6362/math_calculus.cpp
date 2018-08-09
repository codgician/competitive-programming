#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

const double pi = acos(-1.0);

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        double a, b;
        scanf("%lf%lf", &a, &b);
        double ans = 2 * b + pi * a;

        char buf[20];
        sprintf(buf, "%.07lf", ans);
        buf[strlen(buf) - 1] = '\0';
        printf("%s\n", buf);
    }
    return 0;
}