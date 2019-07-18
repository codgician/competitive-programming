#include <bits/stdc++.h>
using namespace std;

#define SIZE 3010

int arr[SIZE][SIZE], height[SIZE][SIZE];

deque<pair<int, int> > mdq;

void push(int val, int pos) {
    while (!mdq.empty() && mdq.back().first > val)
        mdq.pop_back();
    mdq.push_back(make_pair(val, pos));
}

int front(int lim) {
    while (!mdq.empty() && mdq.front().second < lim)
        mdq.pop_front();
    return mdq.front().first;
}

void clear() {
    mdq.clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int row, column, r1, c1;
    long long int g0, x, y, z;
    cin >> row >> column >> r1 >> c1;
    cin >> g0 >> x >> y >> z;

    long long int g = g0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            arr[i][j] = g;
            g = (g * x + y) % z;
        }
    }

    for (int i = 0; i < row; i++) {
        clear();
        for (int j = 0; j < c1; j++)
            push(arr[i][j], j);
        for (int j = 0; j + c1 <= column; j++) {
            height[i][j] = front(j); 
            if (j + c1 < column)
                push(arr[i][j + c1], j + c1);
        }
    }

    for (int j = 0; j + c1 <= column; j++) {
        clear();
        for (int i = 0; i < r1; i++)
            push(height[i][j], i);
        for (int i = 0; i + r1 <= row; i++) {
            height[i][j] = front(i); 
            if (i + r1 < row)
                push(height[i + r1][j], i + r1);
        }
    }

    long long int ans = 0;
    for (int i = 0; i + r1 <= row; i++)
        for (int j = 0; j + c1 <= column; j++)
            ans += height[i][j];
        
    cout << ans <<'\n';

    return 0;
}