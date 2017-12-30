#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int mapping[26];

int main()
{
    ios::sync_with_stdio(false);
    for (int i = 0; i < 26; i++)
    {
        mapping[i] = i;
    }
    string s;
    cin >> s;
    int queryNum;
    cin >> queryNum;
    while (queryNum--)
    {
        char a, b;
        cin >> a >> b;
        swap(mapping[b - 'a'], mapping[a - 'a']);
    }
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = mapping[s[i] - 'a'] + 'a';
    }
    cout << s << endl;
    return 0;
}
