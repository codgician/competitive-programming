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

const long long int lim = 1000000000;

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        long long int n, a, b = -1, c = -1;
        scanf("%lld%lld", &n, &a);
        if (n == 1)
        {
            b = 1;
            c = a + b;
        }
        else if (n == 2)
        {
            // even: a^2 = c^2 - b^2 = (1/4 a^2 + 1)^2 - (1/4 a^2 - 1)^2
            // odd:  a^2 = c^2 - b^2 = (1/2 (a - 1)^2 + (a - 1) + 1)^2 - (1/2 (a - 1)^2 + (a - 1))^2

            if (a & 1)
            {
                b = ((a - 1) >> 1) * (a - 1) + (a - 1);
                c = b + 1;
            }
            else
            {
                b = ((a >> 1) * (a >> 1)) - 1;
                c = ((a >> 1) * (a >> 1)) + 1;
            }
        }

        printf("%lld %lld\n", b, c);
    }

    return 0;
}