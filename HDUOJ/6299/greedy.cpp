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

typedef struct _Node
{
    int leftNum, rightNum;
} Node;

Node arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;

        int ans = 0;
        for (int i = 0; i < num; i++)
        {
            arr[i].leftNum = 0;
            arr[i].rightNum = 0;

            string str;
            cin >> str;
            for (int j = 0; j < (int)str.size(); j++)
            {
                if (str[j] == '(')
                {
                    arr[i].leftNum++;
                }
                else if (str[j] == ')')
                {
                    if (arr[i].leftNum == 0)
                    {
                        arr[i].rightNum++;
                    }
                    else
                    {
                        ans += 2;
                        arr[i].leftNum--;
                    }
                }
            }
        }

        sort(arr + 0, arr + num, [](Node & fst, Node & snd) {
            if (min(fst.leftNum, snd.rightNum) == min(snd.leftNum, fst.rightNum))
            {
                return fst.leftNum > snd.leftNum;
            }
            return min(fst.leftNum, snd.rightNum) > min(snd.leftNum, fst.rightNum);
        });

        int cntLeft = 0;
        for (int i = 0; i < num; i++)
        {
            int newNum = min(cntLeft, arr[i].rightNum);
            cntLeft -= newNum;
            ans += (newNum << 1);
            cntLeft += arr[i].leftNum;
        }

        cout << ans << endl;
    }
    return 0;
}