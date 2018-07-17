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

char fst[SIZE], snd[SIZE];

int main()
{
    int len;
    scanf("%d", &len);
    scanf("%s", fst);
    scanf("%s", snd);

    int ans = 0;
    for (int i = 0; i < (len >> 1); i++)
    {
        char tmp[4];
        tmp[0] = fst[i];
        tmp[1] = fst[len - i - 1];
        tmp[2] = snd[i];
        tmp[3] = snd[len - i - 1];
        sort(tmp + 0, tmp + 4);

        int typeNum = 1;
        for (int j = 1; j < 4; j++)
        {
            if (tmp[j] != tmp[j - 1])
                typeNum++;
        }

        if (tmp[0] == tmp[1] && tmp[2] == tmp[3])
            continue;
        if (typeNum == 2)
        {
            ans++;
        }
        else if (typeNum == 3)
        {
            if (fst[i] == fst[len - i - 1])
                ans += 2;
            else
                ans++;
        }
        else
        {
            ans += 2;
        }
    }

    if (len & 1)
    {
        if (fst[((len + 1) >> 1) - 1] != snd[((len + 1) >> 1) - 1])
            ans++;
    }

    printf("%d\n", ans);
    return 0;
}