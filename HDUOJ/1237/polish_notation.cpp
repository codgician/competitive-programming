// Can only pass when language is set to C++ instead of G++

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
using namespace std;

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int getPriority(char opr)
{
    if (opr == '+' || opr == '-')
        return 1;
    if (opr == '*' || opr == '/')
        return 2;
    return 0;
}

double calc(double fst, double snd, char opr)
{
    if (opr == '+')
        return fst + snd;
    if (opr == '-')
        return fst - snd;
    if (opr == '*')
        return fst * snd;
    if (opr == '/')
        return fst / snd;
    return 0;
}

string getPolish(string &orig)
{
    string ans;
    stack<char> st;
    bool prevIsDigit = false;

    for (int i = 0; i < (int)orig.size(); i++)
    {
        if (orig[i] == ' ')
            continue;

        if (isDigit(orig[i]))
        {
            if (!prevIsDigit)
            {
                prevIsDigit = true;
            }
            ans += orig[i];
            continue;
        }

        if (prevIsDigit)
        {
            ans += ' ';
            prevIsDigit = false;
        }

        if (orig[i] == '(')
        {
            st.push(orig[i]);
            continue;
        }
        else if (orig[i] == ')')
        {
            while (st.top() != '(')
            {
                ans += st.top();
                st.pop();
            }
            st.pop();
        }
        else
        {
            while (!st.empty() && getPriority(orig[i]) <= getPriority(st.top()))
            {
                ans += st.top();
                st.pop();
            }
            st.push(orig[i]);
        }
    }

    ans += ' ';
    while (!st.empty())
    {
        ans += st.top();
        st.pop();
    }

    return ans;
}

long double solve(string &polish)
{
    stack<long double> st;

    int lastStartPt = -1;
    for (int i = 0; i < (int)polish.size(); i++)
    {
        if (polish[i] == ' ')
        {
            if (lastStartPt != -1)
            {
                long double cntNum = 0, tmp = 1;
                for (int j = i - 1; j >= lastStartPt; j--)
                {
                    cntNum += tmp * (polish[j] - '0');
                    tmp *= 10;
                }
                st.push(cntNum);
                lastStartPt = -1;
            }
        }
        else if (isDigit(polish[i]))
        {
            if (lastStartPt == -1)
                lastStartPt = i;
        }
        else
        {
            long double fst = st.top();
            st.pop();
            long double snd = st.top();
            st.pop();

            long double res = calc(snd, fst, polish[i]);
            st.push(res);
        }
    }

    return st.top();
}

int main()
{
    ios::sync_with_stdio(false);
    string str;
    while (getline(cin, str))
    {
        bool isAllZero = true;
        for (int i = 0; i < (int)str.size(); i++)
        {
            if (str[i] != '0')
            {
                isAllZero = false;
                break;
            }
        }

        if (isAllZero)
            break;

        string polish = getPolish(str);
        long double ans = solve(polish);
        cout << fixed << setprecision(2) << ans + 0.0005 << endl;
    }
    return 0;
}