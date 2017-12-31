#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define ISNUMBER false
#define NOTNUMBER true

using namespace std;
string d, nd;
bool hasBlank = false;

bool isNumber(string str)
{
    if (str.length() == 0)
        return false;
    if (str.length() > 1 && str[0] == '0')
        return false;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

void addTo(string str, bool dest)
{
    if (dest == ISNUMBER)
    {
        if (d.length() > 0)
            d = d + ',';
        d = d + str;
    }
    else
    {
        if (hasBlank || nd.length() > 0)
            nd = nd + ',';
        if (str.length() == 0)
            hasBlank = true;
        nd = nd + str;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int sPt = 0;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ';' || s[i] == ',')
        {
            string tmp;
            tmp = s.substr(sPt, i - sPt);
            if (isNumber(tmp))
            {
                addTo(tmp, ISNUMBER);
            }
            else
            {
                addTo(tmp, NOTNUMBER);
            }
            sPt = i + 1;
        }
    }

    string tmp;
    tmp = s.substr(sPt, s.length() - sPt);
    if (isNumber(tmp))
    {
        addTo(tmp, ISNUMBER);
    }
    else
    {
        addTo(tmp, NOTNUMBER);
    }

    if (d.length() == 0)
    {
        cout << "-" << endl;
    }
    else
    {
        cout << "\"" << d << "\"" << endl;
    }

    if (!hasBlank && nd.length() == 0)
    {
        cout << "-" << endl;
    }
    else
    {
        cout << "\"" << nd << "\"" << endl;
    }

    return 0;
}
