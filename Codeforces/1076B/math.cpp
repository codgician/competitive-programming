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

#define SIZE 100010

long long int primeArr[SIZE], factorArr[SIZE];
int primePt;

void initPrime()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initPrime();

    long long int num;
    cin >> num;

    long long int fstPrime = -1; 
    for (int i = 0; i < primePt && primeArr[i] * primeArr[i] <= num; i++)
    {
        if (num % primeArr[i] == 0)
        {
            fstPrime = primeArr[i];
            break;
        }
    }

    if (fstPrime == -1)
    {
        cout << 1 << endl;
        return 0;
    }

    if (fstPrime == 2)
        cout << num / 2 << endl;
    else
        cout << (num - fstPrime) / 2 + 1 << endl;

    return 0;
}