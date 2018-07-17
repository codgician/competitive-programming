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

#define SIZE 2010

typedef struct _Node
{
    int id;
    int val;
} Node;

Node arr[SIZE];
int order[SIZE];

bool cmp(Node & fst, Node & snd)
{
    return fst.val > snd.val;
}

int main()
{
    ios::sync_with_stdio(false);
    int len, num;
    cin >> len >> num;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i].val;
        arr[i].id = i;
    }
    sort(arr + 0, arr + len, cmp);

    long long int ans = 0;
    for (int i = 0; i < num; i++)
    {
        order[i] = arr[i].id;
        ans += arr[i].val;
    }
    sort(order + 0, order + num);

    cout << ans << endl;
    if (num == 1)
    {
        cout << len << endl;
        return 0;
    }
    
    for (int i = 0; i < num - 1; i++)
    {
        if (i == 0)
            cout << order[i] - 0 + 1;
        else
            cout << order[i] - order[i - 1];
        cout << " ";
    }
    cout << len - order[num - 2] - 1 << endl;
    return 0;
}