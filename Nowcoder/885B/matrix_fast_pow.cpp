#include <bits/stdc++.h>
using namespace std;
  
#define SIZE 2
  
int mod;

class Matrix {
public:
    int row, column;
    long long int arr[SIZE][SIZE];

    Matrix(int r, int c) {
        row = r; column = c;
        memset(arr, 0, sizeof(arr));
    }

    void operator += (const Matrix & b) {
        // assert(row == b.row && column == b.column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                arr[i][j] += b.arr[i][j];
                if (arr[i][j] >= mod)
                    arr[i][j] %= mod;
            }
        }
    }

    Matrix operator * (const Matrix & snd) const {
        // assert(column == snd.row);
        Matrix ret(row, snd.column);
        for (int i = 0; i < row; i++) {
            for (int k = 0; k < column; k++) {
                long long int cnt = arr[i][k];
                for (int j = 0; j < column; j++) {
                    ret.arr[i][j] += cnt * snd.arr[k][j];
                    if (ret.arr[i][j] >= mod)
                        ret.arr[i][j] %= mod;
                }
            }
        }
        return ret;
    }

    Matrix & operator = (const Matrix & snd) {
        row = snd.row; column = snd.column;
        memcpy(arr, snd.arr, sizeof(snd.arr));
        return *this;
    }
};
  
Matrix matNaivePow(const Matrix & mat, int n) {
    Matrix ret(mat.row, mat.column);
    for (int i = 0; i < mat.row; i++)
        ret.arr[i][i] = 1;
    while (n--)
        ret = ret * mat;
    return ret;
}
  
Matrix matFastPow(Matrix mat, string & str) {
    // assert(matrix.row == matrix.column);
    Matrix ret(mat.row, mat.column);
    for (int i = 0; i < mat.row; i++)
        ret.arr[i][i] = 1;
    while (str.size()) {
        if (str.back() != '0')
            ret = ret * matNaivePow(mat, str.back() - '0');
        mat = matNaivePow(mat, 10);
        str.pop_back();
    }
    return ret;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
  
    Matrix base(2, 1), trans(2, 2);
    cin >> base.arr[1][0] >> base.arr[0][0];
    cin >> trans.arr[0][0] >> trans.arr[0][1];
    trans.arr[1][0] = 1;
  
    string buf; cin >> buf >> mod;
    if (buf == "0") {
        cout << base.arr[1][0] << '\n';
        return 0;
    }
  
    if (buf == "1") {
        cout << base.arr[0][0] << '\n';
        return 0;
    }
  
    Matrix ans = matFastPow(trans, buf) * base;
    cout << ans.arr[1][0] << '\n';
  
    return 0;
}