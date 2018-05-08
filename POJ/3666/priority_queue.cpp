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
#define SIZE 5010
using namespace std;

int arr[SIZE];


int main()
{
    ios::sync_with_stdio(false);
    int len;
    while (cin >> len)
    {
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
        }

        long long int ans1 = 0;
        priority_queue<int, vector<int>, less<int> > pq1;

        pq1.push(arr[0]);
        for (int i = 1; i < len; i++)
        {
            pq1.push(arr[i]);
            if (pq1.top() > arr[i])
            {
                ans1 += abs(pq1.top() - arr[i]);
                pq1.pop();
                pq1.push(arr[i]);
            }
        }

        long long int ans2 = 0;
        priority_queue<int, vector<int>, greater<int> > pq2;

        pq2.push(arr[0]);
        for (int i = 1; i < len; i++)
        {
            pq2.push(arr[i]);
            if (pq2.top() < arr[i])
            {
                ans2 += abs(pq2.top() - arr[i]);
                pq2.pop();
                pq2.push(arr[i]);
            }
        }

        cout << min(ans1, ans2) << endl;
    }
    return 0;
}