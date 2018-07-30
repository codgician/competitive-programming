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

#define SIZE 100010

int arr[SIZE];

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int num;
        scanf("%d", &num);

        int xorSum = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%d", arr + i);
            xorSum ^= arr[i];
        }

        for (int i = 0; i < num - 1; i++)
        {
            int from, to;
            scanf("%d%d", &from, &to);
        }

        if (xorSum == 0)
        {
            puts("D");
        }
        else
        {
            puts("Q");
        }
    }
    return 0;
}