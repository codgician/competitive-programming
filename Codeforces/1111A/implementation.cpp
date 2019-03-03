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

string fst, snd;

bool isVowel(char ch)
{
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

bool check()
{
    if (fst.size() != snd.size())
        return false;
    int len = fst.size();
    for (int i = 0; i < len; i++)
    {
        if (isVowel(fst[i]) != isVowel(snd[i]))
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> fst >> snd;
    if (check())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}