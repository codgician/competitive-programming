#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int comNum;
    int left = 0, up = 0;
    scanf("%d\n", &comNum);
    for (int i = 0; i < comNum; i++)
    {
        char cmd;
        scanf("%c", &cmd);
        if (cmd == 'U')
            up++;
        else if (cmd == 'D')
            up--;
        else if (cmd == 'L')
            left++;
        else if (cmd == 'R')
            left--;
    }
    printf("%d\n", comNum - (abs(up) + abs(left)));
    return 0;
}
