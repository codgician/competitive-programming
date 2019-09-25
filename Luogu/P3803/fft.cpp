#include <bits/stdc++.h>
using namespace std;

#define SIZE 3000010
const double pi = acos(-1.0);

class Complex {
public:
    double real, imag;
    Complex operator + (const Complex & snd) & { return Complex{real + snd.real, imag + snd.imag}; };
    Complex operator - (const Complex & snd) & { return Complex{real - snd.real, imag - snd.imag}; };
    Complex operator * (const Complex & snd) & { return Complex{real * snd.real - imag * snd.imag, real * snd.imag + imag * snd.real}; };
    Complex conj() & { return Complex{real, -imag}; }
};

Complex fst[SIZE], snd[SIZE], omg[SIZE], inv[SIZE];
int pos[SIZE], fstLen, sndLen, len, lim;

void init() {
    len = 1, lim = 0;
    while (len < fstLen + sndLen - 1)
        len <<= 1, lim++;
    double cnt = 0;
    for (int i = 0; i < len; i++, cnt += pi + pi) {
        omg[i] = {cos(cnt / len), sin(cnt / len)};
        inv[i] = omg[i].conj();
        pos[i] = (pos[i >> 1] >> 1) | ((i & 1) << (lim - 1)) ;
    }
}

void fft(Complex * arr, Complex * omg) {
    for (int i = 0; i < len; i++) 
        if (i < pos[i])
            swap(arr[i], arr[pos[i]]);
    for (int l = 2; l <= len; l <<= 1) {
        int midPt = l >> 1, step = len / l;
        for (Complex * p = arr; p != arr + len; p += l) {
            for (int i = 0, cnt = 0; i < midPt; i++, cnt += step) {
                Complex t = omg[cnt] * p[i + midPt];
                p[i + midPt] = p[i] - t; p[i] = p[i] + t;
            }
        }
    }
}

void multiply() {
    init();
    fft(fst, omg); fft(snd, omg);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * snd[i];
    fft(fst, inv);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> fstLen >> sndLen; fstLen++; sndLen++;
    for (int i = 0; i < fstLen; i++) {
        int cnt; cin >> cnt; fst[i].real = cnt;
    }
    for (int i = 0; i < sndLen; i++) {
        int cnt; cin >> cnt; snd[i].real = cnt;
    }
    multiply();

    cout << (int)(fst[0].real / len + 0.5);
    for (int i = 1; i < fstLen + sndLen - 1; i++)
        cout << ' ' << (int)(fst[i].real / len + 0.5);
    cout << '\n';

    return 0;   
}