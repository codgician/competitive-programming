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

#define SIZE 310

long long int arr[SIZE], fst[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int vertexNum;
    cin >> vertexNum;

    for (int i = 0; i < vertexNum; i++)
        cin >> arr[i];
    
    sort(arr + 0, arr + vertexNum);

    int cntPt = 0;
    for (int i = vertexNum - 1; cntPt < vertexNum && i >= 0; i--)
    {
        fst[cntPt] = arr[i];
        cntPt += 2;
    }
    cntPt = 1;
    for (int i = 0; cntPt < vertexNum && i < vertexNum; i++)
    {
        fst[cntPt] = arr[i];
        cntPt += 2;
    }

    long long int fstAns = 0;
    for (int i = 0; i < vertexNum - 1; i++)
    {
        fstAns += (fst[i] - fst[i + 1]) * (fst[i] - fst[i + 1]);
    }

    cout << fstAns + fst[0] * fst[0] << endl;

    return 0;
}