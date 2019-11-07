import java.io.*;
import java.util.*;
import java.math.*;
 
public class Main {
    public static int isPrime(int num) {
        for (int i = 2; i * i <= num; i++)
            if (num % i == 0)
                return 0;
        return 1;
    }
 
    static BigInteger __gcd(BigInteger a, BigInteger b) {
        if (a.compareTo(b) == -1) {
            BigInteger tmp = b; b = a; a = tmp;
        }
        while (b.compareTo(BigInteger.valueOf(0)) == 1) {
            BigInteger tmp = a.mod(b); a = b; b = tmp;
        }
        return a;
    }
 
    public static void main(String[] args) {
        Scanner scn = new Scanner(System.in);
        int caseNum = scn.nextInt();
        for (int t = 0; t < caseNum; t++) {
            BigInteger num = scn.nextBigInteger();
            BigInteger cnt = BigInteger.ONE, sum = BigInteger.ONE;
 
            for (int i = 2; ; i++) {
                if (isPrime(i) == 0)
                    continue;
                BigInteger nxt = cnt.multiply(BigInteger.valueOf(i));
                if (nxt.compareTo(num) == 1)
                    break;
                cnt = nxt;
                sum = sum.multiply(BigInteger.valueOf(i + 1));
            }
 
            BigInteger gcd = __gcd(cnt, sum);
            System.out.println(cnt.divide(gcd) + "/" + sum.divide(gcd));
        }
    }
}