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
#include <random>
#include <chrono>
using namespace std;

#define SIZE 1000010
#define QSIZE 62

int pool[SIZE], arr[QSIZE];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int qNum = 60;

int query(char opr, int val)
{
    qNum--;
    cout << opr << " " << val << endl;
    int ret;
    cin >> ret;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    srand(time(NULL));

    int len;
    cin >> len;

    // Find maximum value
    int leftPt = 0, rightPt = 1e9;
    int ans = -1;
    while (leftPt <= rightPt)
    {
        int midPt = (leftPt + rightPt) >> 1;
        int ret = query('>', midPt);
        if (ret == 1)
        {
            ans = midPt;
            leftPt = midPt + 1;
        }
        else
        {
            rightPt = midPt - 1;
        }
    }

    for (int i = 0; i < len; i++)
        pool[i] = i;
    int rangePt = len - 1, arrPt = 0;
    while (rangePt >= 0 && qNum > 0)
    {
        int rnd = rng() % (rangePt + 1);
        arr[arrPt++] = query('?', pool[rnd] + 1);
        swap(pool[rnd], pool[rangePt--]);
    }
    sort(arr + 0, arr + arrPt);
    int delta = 0;
    for (int i = 1; i < arrPt; i++)
        delta = __gcd(delta, abs(arr[i] - arr[i - 1]));

    int fst = ans + 1 - (len - 1) * delta;
    cout << "! " << fst << " " << delta << endl;

    return 0;
}