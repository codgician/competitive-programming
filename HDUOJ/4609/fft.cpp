#include <bits/stdc++.h>
using namespace std;

#define SIZE 330030
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
    len = 1, lim = 0; double cnt = 0;
    while (len < fstLen + sndLen - 1)
        len <<= 1, lim++;
    for (int i = 0; i < len; i++, cnt += pi + pi) {
        omg[i] = {cos(cnt / len), sin(cnt / len)};
        inv[i] = omg[i].conj(); pos[i] = (pos[i >> 1] >> 1) | ((i & 1) << (lim - 1)) ;
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
    init(); fft(fst, omg); fft(snd, omg);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * snd[i];
    fft(fst, inv);
}

int arr[SIZE]; long long int twos[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int num; fstLen = 0, sndLen = 0; cin >> num;
        long long int tot = 1ll * num * (num - 1) * (num - 2) / 6;
        fill(fst + 0, fst + SIZE, Complex{0, 0});
        fill(snd + 0, snd + SIZE, Complex{0, 0});
        for (int i = 0; i < num; i++)
            cin >> arr[i], fst[arr[i]].real++, snd[arr[i]].real++;
        sort(arr + 0, arr + num); fstLen = arr[num - 1] + 1; sndLen = fstLen;
        multiply();
        for (int i = 0; i < fstLen + sndLen - 1; i++)
            twos[i] = fst[i].real / len + 0.5;
        for (int i = 0; i < num; i++)
            twos[arr[i] << 1]--;
        for (int i = 0; i < fstLen + sndLen - 1; i++)
            twos[i] >>= 1;
        for (int i = 1; i < fstLen + sndLen - 1; i++)
            twos[i] += twos[i - 1];
        
        long long int ans = 0;
        for (int i = 0; i < num; i++) {
            ans += twos[fstLen + sndLen - 2] - twos[arr[i]];
            ans -= (1ll * (num - i - 1) * (num - i - 2)) >> 1;
            ans -= 1ll * (num - i - 1) * i;
            ans -= num - 1;
        }
        cout << fixed << setprecision(7) << (double)ans / tot << '\n'; 
    }

    return 0;
}