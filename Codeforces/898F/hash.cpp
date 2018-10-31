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
using namespace std;

#define MOD_SIZE 5
#define SIZE 1000100

long long int hashArr[MOD_SIZE][SIZE], tenPowArr[MOD_SIZE][SIZE];
long long int modArr[MOD_SIZE] = {19260817, 47868179, 65007583, 998244353, 1000000007};
int len;

string str;

void initTenPow(int initSize)
{
    for (int i = 0; i < MOD_SIZE; i++)
    {
        tenPowArr[i][0] = 1;
    }

    for (int i = 1; i <= initSize; i++)
    {
        for (int j = 0; j < MOD_SIZE; j++)
        {
            tenPowArr[j][i] = tenPowArr[j][i - 1] * 10 % modArr[j];
        }
    }
}

bool check(int fstPt, int sndPt)
{
    if (fstPt >= sndPt || fstPt < 0 || sndPt >= len - 1)
        return false;

    if (str[0] == '0' && fstPt > 0)
        return false;
    if (str[fstPt + 1] == '0' && sndPt > fstPt + 1)
        return false;
    if (str[sndPt + 1] == '0' && len - 1 > sndPt + 1)
        return false;

    for (int i = 0; i < MOD_SIZE; i++)
    {
        long long int fstHash = hashArr[i][fstPt];
        long long int sndHash = (hashArr[i][sndPt] - hashArr[i][fstPt] * tenPowArr[i][sndPt - fstPt] % modArr[i] + modArr[i]) % modArr[i];
        long long int thdHash = (hashArr[i][len - 1] - hashArr[i][sndPt] * tenPowArr[i][len - 1 - sndPt] % modArr[i] + modArr[i]) % modArr[i];

        if ((fstHash + sndHash) % modArr[i] != thdHash)
            return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> str;
    len = str.size();

    initTenPow(len);

    for (int i = 0; i < MOD_SIZE; i++)
    {
        hashArr[i][0] = (str[0] - '0') % modArr[i];
    }
    
    for (int i = 1; i < len; i++)
    {
        for (int j = 0; j < MOD_SIZE; j++)
        {
            hashArr[j][i] = (hashArr[j][i - 1] * 10 + (str[i] - '0')) % modArr[j];
        }
    }

    int fstPt = -1, sndPt = -1;
    for (int i = 0; i < len; i++)
    {
        // len3 = len1
        if (check(i, len - i - 2))
        {
            fstPt = i, sndPt = len - i - 2;
            break;
        }

        // len3 = len1 + 1
        if (check(i, len - i - 3))
        {
            fstPt = i, sndPt = len - i - 3;
            break;
        }

        // len3 = len2
        if (check(len - (i << 1) - 3, len - i - 2))
        {
            fstPt = len - (i << 1) - 3, sndPt = len - i - 2;
            break; 
        }

        // len3 = len2 + 1 
        if (check(len - (i << 1) - 4, len - i - 3))
        {
            fstPt = len - (i << 1) - 4, sndPt = len - i - 3;
            break;
        }
    }

    assert(fstPt != -1 && sndPt != -1);

    for (int i = 0; i <= fstPt; i++)
        cout << str[i];
    cout << "+";
    for (int i = fstPt + 1; i <= sndPt; i++)
        cout << str[i];
    cout << "=";
    for (int i = sndPt + 1; i < len; i++)
        cout << str[i];
    cout << endl;

    return 0;
}