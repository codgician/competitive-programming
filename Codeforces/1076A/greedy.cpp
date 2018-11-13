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
#include <cassert>
using namespace std;

#define SIZE 200010

char str[SIZE];

int main()
{
    int len;
    scanf("%d", &len);
    scanf("%s", str);

    int erasePt = len - 1;
    for (int i = 0; i < len - 1; i++)
    {
        if (str[i] > str[i + 1])
        {
            erasePt = i;
            break;
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (i == erasePt)
            continue;
        printf("%c", str[i]);
    }
    printf("\n");

    return 0;
}