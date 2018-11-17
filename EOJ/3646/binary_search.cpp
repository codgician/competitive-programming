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
#include <cassert>
using namespace std;

long long int wrongPt, cntPt;
long long int n, k;

int encodeChr(char ch)
{
    if (ch == '>')
        return -1;
    if (ch == '=')
        return 0;
    return 1;
}

int ask(long long int val)
{
    cout << val << endl << flush;
    char ch1;
    cin >> ch1;

    if (ch1 == '=')
        return encodeChr(ch1);
    
    if (wrongPt != -1)
    {
        int ret = encodeChr(ch1);
        if (cntPt == wrongPt)
            ret = -ret;
        cntPt = (cntPt + 1) % k;
        return ret;
    }

    cout << val << endl << flush;
    char ch2;
    cin >> ch2;

    if (ch1 == ch2)
    {
        // Must be truth
        cntPt = (cntPt + 2) % k;
        return encodeChr(ch1);
    }

    cout << val << endl << flush;
    char ch3;
    cin >> ch3;

    // Something went wrong
    if (ch1 == ch3)
    {
        wrongPt = (cntPt + 1) % k;
        cntPt = (cntPt + 3) % k;
        return encodeChr(ch1);
    }
   
    wrongPt = cntPt;
    cntPt = (cntPt + 3) % k;
    return encodeChr(ch2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;

    long long int leftPt = 1, rightPt = (1ll << n) - 1;
    cntPt = 0, wrongPt = -1;
    if (k == 1)
        wrongPt = 0;
    else if (k == 2)
    {
        cout << 1 << endl << flush;
        cntPt = 1;
        char ch;
        cin >> ch;
        if (ch == '=')
            return 0;
        if (ch == '>')
            wrongPt = 0;
        else
            wrongPt = 1;
    }

    while (leftPt <= rightPt)
    {
        long long int midPt = (leftPt + rightPt) >> 1;
        int cnt = ask(midPt);

        if (cnt == 0)
            return 0;

        if (cnt == -1)
            rightPt = midPt - 1;
        else
            leftPt = midPt + 1;
    }

    int cnt = ask(leftPt);
    assert(cnt == 0);

    return 0;
}