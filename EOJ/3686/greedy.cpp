#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000010

long long int arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int len;
    cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    long long int leftSum = arr[0], rightSum = arr[len - 1];
    int leftPt = 1, rightPt = len - 2, ans = 0;

    while (leftPt <= rightPt) {
        while (leftPt < rightPt && leftSum < rightSum) {
            leftSum += arr[leftPt++];
            ans++;
        }
        while (leftPt < rightPt && rightSum < leftSum) {
            rightSum += arr[rightPt--];
            ans++;
        }

        if (leftPt == rightPt && leftSum != rightSum) {
            if (leftSum < rightSum)
                leftSum += arr[leftPt];
            else
                rightSum += arr[rightPt];
            ans++;
        }

        if (leftSum == rightSum) {
            leftSum = arr[leftPt++], rightSum = arr[rightPt--];
        }

        if (leftPt >= rightPt && leftSum != rightSum) {
            ans++;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}