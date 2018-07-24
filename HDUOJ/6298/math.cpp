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

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;
        if (num % 3 == 0)
        {
            cout << (long long int)(num / 3) * (num / 3) * (num / 3) << endl;
        }
        else if (num % 4 == 0)
        {
            cout << (long long int)(num >> 2) * (num >> 2) * (num >> 1) << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}