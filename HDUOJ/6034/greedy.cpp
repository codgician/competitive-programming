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

#define SIZE 110000

const long long int mod = 1e9 + 7;

typedef struct _Node
{
    int ch;
    long long int weight[SIZE];
    int maxPos;
    bool canBeZero;
} Node;

Node arr[26];
string strArr[SIZE];
int valArr[26];

long long int twentySix[SIZE];

void init()
{
    twentySix[0] = 1;
    for (int i = 1; i < SIZE; i++)
        twentySix[i] = twentySix[i - 1] * 26 % mod;
}

bool cmp(Node & fst, Node & snd)
{
    if (fst.maxPos == snd.maxPos)
    {
        for (int i = fst.maxPos; i >= 0; i--)
        {
            if (fst.weight[i] != snd.weight[i])
            {
                return fst.weight[i] < snd.weight[i];
            }
        }
        return false;
    }

    return fst.maxPos < snd.maxPos;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int num, casePt = 0;
    while (cin >> num)
    {
        for (int i = 0; i < 26; i++)
        {
            arr[i].ch = i;
            arr[i].maxPos = 0;
            arr[i].canBeZero = true;
            memset(arr[i].weight, 0, sizeof(arr[i].weight));
            valArr[i] = -1;
        }

        for (int i = 0; i < num; i++)
        {
            cin >> strArr[i];
            int cntPos = 0;
            for (string::reverse_iterator rit = strArr[i].rbegin(); rit != strArr[i].rend(); ++rit)
            {
                int cnt = *rit - 'a';
                arr[cnt].weight[cntPos]++;
                arr[cnt].maxPos = max(arr[cnt].maxPos, cntPos);
                if (cntPos > 0 && cntPos == (int)strArr[i].size() - 1)
                    arr[cnt].canBeZero = false;
                cntPos++;
            }
        }

        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j <= arr[i].maxPos; j++)
            {
                if (arr[i].weight[j] >= 26)
                {
                    arr[i].weight[j + 1] += arr[i].weight[j] / 26;
                    arr[i].weight[j] %= 26;
                    arr[i].maxPos = max(arr[i].maxPos, j + 1);
                }
            }
        }

        sort(arr + 0, arr + 26, cmp);

        for (int i = 0; i < 26; i++)
        {
            if (arr[i].canBeZero)
            {
                valArr[arr[i].ch] = 0;
                break;
            }
        }
        int cntVal = 1;
        for (int i = 0; i < 26; i++)
        {
            if (valArr[arr[i].ch] == -1)
            {
                valArr[arr[i].ch] = cntVal++;
            }
        }

        long long int ans = 0;
        for (int i = 0; i < num; i++)
        {
            int cntPos = 0;
            for (string::reverse_iterator rit = strArr[i].rbegin(); rit != strArr[i].rend(); ++rit)
            {
                int cnt = *rit - 'a';
                ans += twentySix[cntPos++] * valArr[cnt] % mod;
                ans %= mod;
            }
        }
        cout << "Case #" << ++casePt << ": " << ans << endl;
    }
    return 0;
}
