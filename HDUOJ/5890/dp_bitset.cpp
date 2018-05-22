#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#include <bitset>
#define BAG_SIZE 90
#define CARD_SIZE 55
#define SELECT_SIZE 12
#define DEL_SIZE 4
using namespace std;

bitset<BAG_SIZE> dp[SELECT_SIZE];
bool ans[CARD_SIZE][CARD_SIZE][CARD_SIZE];
int arr[CARD_SIZE], remArr[DEL_SIZE];
int num;

inline void work(int fst, int snd, int thd)
{
    for (int i = 0; i <= 10; i++)
    {
        dp[i].reset();
    }
    dp[0][0] = 1;

    for (int i = 1; i <= num; i++)
    {
        if (i == fst || i == snd || i == thd || arr[i] >= 87)
            continue;

        for (int j = 9; j >= 0; j--)
        {
            dp[j + 1] |= (dp[j] << arr[i]);
        }
    }

    if (dp[10][87])
        ans[fst][snd][thd] = true;
    else
        ans[fst][snd][thd] = false;
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        scanf("%d", &num);
        for (int i = 1; i <= num; i++)
        {
            scanf("%d", arr + i);
        }

        for (int i = 1; i <= num; i++)
        {
            for (int j = i; j <= num; j++)
            {
                for (int k = j; k <= num; k++)
                {
                    work(i, j, k);
                }
            }
        }

        int qNum;
        scanf("%d", &qNum);
        while (qNum--)
        {
            for (int i = 0; i < 3; i++)
            {
                scanf("%d", remArr + i);
            }
            sort(remArr + 0, remArr + 3);

            if (ans[remArr[0]][remArr[1]][remArr[2]])
                puts("Yes");
            else
                puts("No");
        }
    }
    return 0;
}