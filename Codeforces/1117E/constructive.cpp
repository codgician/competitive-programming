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
#include <bitset>
#include <cassert>
using namespace std;

#define SIZE 17600

int idArr[SIZE][3], mpArr[SIZE];
string askArr[3], retArr[3];

string query(string & str)
{
    cout << "? " << str << endl << flush;
    string ret;
    cin >> ret;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string cipher;
    cin >> cipher;
    int len = cipher.size();

    for (int i = 0; i < len; i++)
    {
        int cnt = i;
        for (int j = 0; j < 3; j++)
        {
            idArr[i][j] = cnt % 26;
            cnt /= 26;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        askArr[i].clear();
        for (int j = 0; j < len; j++)
        {
            char ch = 'a' + idArr[j][i];
            askArr[i].push_back(ch);
        }
        retArr[i] = query(askArr[i]);
    }

    for (int i = 0; i < len; i++)
    {
        int askId = 0, retId = 0;
        for (int j = 2; j >= 0; j--)
        {
            askId = askId * 26 + (askArr[j][i] - 'a');
            retId = retId * 26 + (retArr[j][i] - 'a');
        }
        mpArr[retId] = askId;
    }

    string plain = cipher;
    for (int i = 0; i < len; i++)
    {
        plain[i] = cipher[mpArr[i]];
    }
    cout << "! " << plain << endl;

    return 0;
}