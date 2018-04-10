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
#include <set>
#include <map>
#define SIZE 1000100
using namespace std;

int nextArr[SIZE];

void initNext(string &str, int length)
{
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < length; i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum]) // (matchNum + 1) - 1
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int length, casePt = 0;
    while (cin >> length)
    {
        if (length == 0)
            break;

        string str;
        cin >> str;
        initNext(str, length);
        cout << "Test case #" << ++casePt << endl;
        for (int i = 2; i <= length; i++)
        {
            if (i % (i - nextArr[i - 1]) == 0 && i / (i - nextArr[i - 1]) > 1)
            {
                cout << i << " " << i / (i - nextArr[i - 1]) << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
