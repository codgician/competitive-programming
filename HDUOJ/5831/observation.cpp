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

char str[SIZE];
int pfxArr[SIZE], sfxArr[SIZE];

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int len;
        scanf("%d", &len);
        scanf("%s", str + 1);

        pfxArr[0] = 0;
        for (int i = 1; i <= len; i++)
        {
            if (str[i] == '(')
                pfxArr[i] = 1;
            else
                pfxArr[i] = -1;
            pfxArr[i] += pfxArr[i - 1];
        }

        bool ans = true;
        if (pfxArr[len] != 0)
        {
            ans = false;
        }
        else if (len == 2 && str[1] == '(')
        {
            ans = false;
        }
        else
        {
            int fstPt = -1, sndPt = -1;
            for (int i = 1; i <= len; i++)
            {
                if (pfxArr[i] == -1)
                {
                    fstPt = i;
                    break;
                }
            }
            for (int i = len; i >= 1; i--)
            {
                if (pfxArr[len] - pfxArr[i - 1] == 1)
                {
                    sndPt = i;
                    break;
                }
            }

            if (fstPt == -1 || sndPt == -1)
            {
                ans = true;
            }
            else
            {
                swap(str[fstPt], str[sndPt]);

                pfxArr[0] = 0;
                for (int i = 1; i <= len; i++)
                {
                    if (str[i] == '(')
                        pfxArr[i] = 1;
                    else
                        pfxArr[i] = -1;
                    pfxArr[i] += pfxArr[i - 1];

                    if (pfxArr[i] < 0)
                    {
                        ans = false;
                        break;
                    }
                }
            }
        }

        if (ans)
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}