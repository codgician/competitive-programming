#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define CNT_SIZE 1010
#define CHAR_SIZE 40

int arr[SIZE][CHAR_SIZE];
char str[SIZE];
char cnt[CNT_SIZE];

int getId(char ch) {
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a';
    if (ch >= '0' && ch <= '9')
        return ch - '0' + 26;
    assert(false);
    return -1;
}

int main() {
    scanf("%s", str);
    int len = strlen(str);
    for (int j = 0; j < CHAR_SIZE; j++)
        arr[0][j] = -1;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < CHAR_SIZE; j++)
            arr[i + 1][j] = arr[i][j];
        arr[i + 1][getId(str[i])] = i;
    }

    int qNum;
    scanf("%d", &qNum);
    while (qNum--) {
        scanf("%s", cnt);
        int cntLen = strlen(cnt), cntPt = len;
        for (int i = cntLen - 1; i >= 0; i--) {
            cntPt = arr[cntPt][getId(cnt[i])];
            if (cntPt == -1)
                break;
        }

        if (cntPt == -1)
            printf("NO\n");
        else
            printf("YES\n");
    }

    return 0;
}