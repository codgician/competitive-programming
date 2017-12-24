#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

void returnError()
{
    cout << -1 << endl;
    exit(0);
}

int main()
{
    ios::sync_with_stdio(false);
    int father, mother, son, masha;
    cin >> father >> mother >> son >> masha;

    int v3 = max(son, masha);
    if (v3 > (son << 1) || v3 > (masha << 1))
    {
        returnError();
    }

    int v2 = max(mother, max((masha << 1) + 1, v3 + 1));
    if (v2 > (mother << 1))
    {
        returnError();
    }

    int v1 = max(father, max((masha << 1) + 1, v2 + 1));
    if (v1 > (father << 1))
    {
        returnError();
    }

    cout << v1 << endl << v2 << endl << v3 << endl;
    return 0;
}
