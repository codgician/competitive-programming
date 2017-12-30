#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 1501
using namespace std;

int arr[SIZE];

void print(bool isOdd)
{
    cout << (isOdd ? "odd" : "even") << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int pSize;
    cin >> pSize;
    int pNum = 0;
    for (int i = 0; i < pSize; i++)
    {
        cin >> arr[i];
    }
    int pSum = 0;
    for (int i = 0; i < pSize - 1; i++)
    {
        for (int j = i + 1; j < pSize; j++)
        {
            if (arr[i] > arr[j])
            {
                pSum++;
            }
        }
    }
    int oprNum;
    cin >> oprNum;
    while (oprNum--)
    {
        int a, b;
        cin >> a >> b;
        if (a == b)
        {
            print(pSum & 1);
        }
        else
        {
            if (a > b)
                swap(a, b);
            int leftPt = a - 1, rightPt = b - 1;
            while (leftPt < rightPt)
            {
                if (arr[rightPt] < arr[leftPt])
                    pSum--;
                if (arr[leftPt] < arr[rightPt])
                    pSum++;
                swap(arr[leftPt], arr[rightPt]);
                leftPt++;
                rightPt--;
            }
            cout << endl;
            print(pSum & 1);
        }
    }
    return 0;
}
