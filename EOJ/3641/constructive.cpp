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

#define SIZE 200010

int arr[SIZE];

void printCycle(int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << (((i / 3) & 1) ? 3 - (i % 3) : (i % 3) + 1);
        if (i < len - 1)
            cout << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    while (cin >> num)
    {
        if (num <= 3 || num % 3 == 1)
        {
            cout << "Impossible" << endl;
            continue;
        }

    	if (num % 6 == 0)
    	{
    		printCycle(num);
        }
        else if (num % 6 == 2)
        {
            // 6n + 8
            cout << "1 2 1 2 3 2 3 1" << endl;
            printCycle(num - 8);
        }
        else if (num % 6 == 3)
        {
            // 6n + 9
            cout << "1 1 1 1 1 2 3 3 2" << endl;
            printCycle(num - 9);
        }
        else if (num % 6 == 5)
        {
            // 6n + 5
            cout << "1 2 2 1 3" << endl;
            printCycle(num - 5);
        }
    }

    return 0;
}