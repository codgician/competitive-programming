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
#define SIZE 101
using namespace std;

string arr[SIZE];
int nextArr[SIZE];

void initNext(string &str)
{
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < (int)str.length(); i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum]) // (matchNum + 1) - 1
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

bool kmp(string &a, string &b)
{
    for (int i = 0, matchNum = 0; i < (int)a.length(); i++)
    {
        while (matchNum > 0 && (matchNum== (int)b.length() || a[i] != b[matchNum]))
            matchNum = nextArr[matchNum - 1];
        if (a[i] == b[matchNum])
            matchNum++;
        if (matchNum == (int)b.length())
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    string a, b;
    while (cin >> a >> b)
    {
        a += a;
        bool ans = kmp(a, b);
        if (ans)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
