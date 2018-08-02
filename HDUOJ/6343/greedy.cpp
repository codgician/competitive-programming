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

#define SIZE 100010

long long int arr[SIZE];

long long int getVal(int fst, int snd)
{
    return sqrt(abs(arr[fst] - arr[snd]));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int vertexNum;
        cin >> vertexNum;
        for (int i = 0; i < vertexNum; i++)
        {
            cin >> arr[i];
        }

        long long int ans = getVal(0, vertexNum - 1); 
        cout << ans << endl;
    }

    return 0;
}