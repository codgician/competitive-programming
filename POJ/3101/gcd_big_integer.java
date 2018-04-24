import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    
    static int[] arr = new int[1001];
    static BigInteger[] numeratorArr = new BigInteger[1001];
    static BigInteger[] denominatorArr = new BigInteger[1001];

    static BigInteger getGcd(BigInteger a, BigInteger b) {
        if (a.compareTo(b) == -1) {
            BigInteger tmp = b;
            b = a;
            a = tmp;
        }

        while (b.compareTo(BigInteger.valueOf(0)) == 1) {
            BigInteger tmp = a.mod(b);
            a = b;
            b = tmp;
        }

        return a;
    }

    static BigInteger getLcm(BigInteger a, BigInteger b) {
        BigInteger gcd = getGcd(a, b);
        return a.divide(gcd).multiply(b);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner (new BufferedInputStream(System.in));
        while (scanner.hasNext()) {
            int planetNum = scanner.nextInt();
            for (int i = 0; i < planetNum; i++) {
                arr[i] = scanner.nextInt();
                if (i > 0) {
                    numeratorArr[i] = BigInteger.valueOf(arr[i] * arr[0]);
                    denominatorArr[i] = BigInteger.valueOf(Math.abs(arr[i] - arr[0]) * 2);

                    BigInteger gcd = getGcd(numeratorArr[i], denominatorArr[i]);
                    numeratorArr[i] = numeratorArr[i].divide(gcd);
                    denominatorArr[i] = denominatorArr[i].divide(gcd);
                }
            }

            BigInteger numeratorLcm = numeratorArr[1];
            for (int i = 2; i < planetNum; i++) {
                numeratorLcm = getLcm(numeratorLcm, numeratorArr[i]);
            }
            BigInteger denominatorGcd = denominatorArr[1];
            for (int i = 2; i < planetNum; i++) {
                denominatorGcd = getGcd(denominatorGcd, denominatorArr[i]);
            }

            BigInteger gcd = getGcd(numeratorLcm, denominatorGcd);
            numeratorLcm = numeratorLcm.divide(gcd);
            denominatorGcd = denominatorGcd.divide(gcd);

            System.out.println(numeratorLcm + " " + denominatorGcd);
        }
    }
}