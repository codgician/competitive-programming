#include <bits/stdc++.h>
using namespace std;
 
#define SIZE 510
 
int scr[SIZE][SIZE];
int d[SIZE][SIZE], s[SIZE][SIZE], edges[SIZE][SIZE], vertexNum;
 
void floyd() {
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
            s[i][j] = edges[i][j];
    for (int k = 0; k < vertexNum; k++)
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
                if (s[i][k] != 0 && s[k][j] != 0)
                    s[i][j] = max(s[i][j], min(s[i][k], s[k][j]));
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    int cosNum, evaNum; cin >> cosNum >> evaNum;
    for (int i = 0; i < evaNum; i++) {
        for (int j = 0; j < cosNum; j++) {
            cin >> scr[i][j];
            if (scr[i][j] == 0)
                scr[i][j] = INT_MAX;
        }
    }
 
    for (int i = 0; i < cosNum; i++)
        for (int j = 0; j < cosNum; j++)
            d[i][j] = 0;
    for (int i = 0; i < evaNum; i++) {
        for (int j = 0; j < cosNum; j++) {
            for (int k = j + 1; k < cosNum; k++) {
                d[j][k] += (scr[i][j] < scr[i][k]);
                d[k][j] += (scr[i][k] < scr[i][j]);
            }
        }
    }
 
    vertexNum = cosNum;
    for (int i = 0; i < cosNum; i++) {
        edges[i][i] = 0;
        for (int j = i + 1; j < cosNum; j++)
            edges[i][j] = 0, edges[j][i] = 0;
    }
    for (int i = 0; i < cosNum; i++) {
        for (int j = i + 1; j < cosNum; j++) {
            if (d[i][j] == d[j][i])
                continue;
            d[i][j] > d[j][i] ? edges[i][j] = d[i][j] : edges[j][i] = d[j][i];
        }
    }
    floyd();
 
    for (int i = 0; i < cosNum; i++) {
        const auto check = [i, cosNum]() {
            for (int j = 0; j < cosNum; j++) {
                if (i == j)
                    continue;
                if (s[i][j] < s[j][i])
                    return false;
            }
            return true;
        };
 
        if (check())
            cout << i + 1 << ' ';
    }
    cout << '\n';
 
    return 0;
}