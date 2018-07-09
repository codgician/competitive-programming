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
    long long int leftArr[2], rightArr[2];
    while (cin >> leftArr[0] >> rightArr[0] >> leftArr[1] >> rightArr[1])
    {
        long long int ans = 0;
        long long int is2018[2], is1009Odd[2], isEven[2]; 
        for (int i = 0; i < 2; i++)
        {
            is2018[i] = rightArr[i] / 2018 - leftArr[i] / 2018 + (leftArr[i] % 2018 == 0 ? 1 : 0);
            is1009Odd[i] = rightArr[i] / 1009 - leftArr[i] / 1009 + (leftArr[i] % 1009 == 0 ? 1 : 0) - is2018[i];
            isEven[i] = rightArr[i] / 2 - leftArr[i] / 2 + (leftArr[i] % 2 == 0 ? 1 : 0);
        }

        ans += is2018[0] * (rightArr[1] - leftArr[1] + 1) + is2018[1] * (rightArr[0] - leftArr[0] + 1) - is2018[0] * is2018[1];
        ans += is1009Odd[0] * (isEven[1] - is2018[1]) + is1009Odd[1] * (isEven[0] - is2018[0]);
        cout << ans << endl;
    }
    return 0;
}