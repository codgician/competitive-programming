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

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cout << 0;
            if (i < num - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}