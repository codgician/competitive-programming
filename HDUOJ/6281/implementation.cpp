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
#define SIZE 1010
using namespace std;

typedef struct _Node
{
    int origId;
    long long int numerator, denominator;
} Node;

Node arr[SIZE];

bool cmpRule(Node fst, Node snd)
{
    long long int leftTmp = fst.numerator * snd.denominator;
    long long int rightTmp = fst.denominator * snd.numerator;

    if (leftTmp == rightTmp)
        return fst.origId < snd.origId;
    return leftTmp > rightTmp; 
}

int main()
{
    ios::sync_with_stdio(false);
    int num;
    while (cin >> num)
    {
        for (int i = 0; i < num; i++)
        {
            long long int a, b, c;
            cin >> a >> b >> c;

            arr[i].origId = i;
            arr[i].numerator = c;
            arr[i].denominator = a + b;
        }

        sort(arr + 0, arr + num, cmpRule);

        for (int i = 0; i < num; i++)
        {
            cout << arr[i].origId + 1;
            if (i < num - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}